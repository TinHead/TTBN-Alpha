import tornado.web
import tornado.websocket
import tornado.ioloop
import os.path

# This is our WebSocketHandler - it handles the messages
# from the tornado server
class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("index.html")

class WebSocketHandler(tornado.websocket.WebSocketHandler):
    # the client connected
	def open(self):
		print "New client connected"
		self.write_message("You are connected")

	# the client sent the message
	def on_message(self, message):
		self.write_message(message)
		print message

	# client disconnected
	def on_close(self):
		print "Client disconnected"



class Application(tornado.web.Application):
    def __init__(self):
        handlers = [
	   (r"/command", WebSocketHandler),
    	   (r"/",MainHandler),
        ]
        settings = dict(
          # cookie_secret="__TODO:_GENERATE_YOUR_OWN_RANDOM_VALUE_HERE__",
            template_path=os.path.join(os.path.dirname(__file__), "templates"),
            static_path=os.path.join(os.path.dirname(__file__), "static"),
          ##  xsrf_cookies=True,
        )
        tornado.web.Application.__init__(self, handlers, **settings)

# start the tornado server on port 8888
def main():
	app = Application()
	app.listen(8888)
	tornado.ioloop.IOLoop.instance().start()

if __name__ == "__main__":
	main()    

