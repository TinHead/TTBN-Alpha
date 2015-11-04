#!/usr/bin/python

import tornado.web
import tornado.websocket
import tornado.ioloop
import pigpio
from time import sleep
import os.path

pigpio.start(port='8889')
#
cam_value = 1400
#
pigpio.set_servo_pulsewidth(7,0)
pigpio.set_servo_pulsewidth(8,0)
pigpio.set_servo_pulsewidth(24,cam_value)

# This is our WebSocketHandler - it handles the messages
# from the tornado server
class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("index.html")

class WebSocketHandler(tornado.websocket.WebSocketHandler):
    cam_value = 1400
    # the client connected
    def open(self):
        print "New client connected"
        self.write_message("You are connected")

    # the client sent the message
    def on_message(self, message):
        self.write_message(message)
        if message == '38':
            #up
            print 'up'
            pigpio.set_servo_pulsewidth(7,2500)
            pigpio.set_servo_pulsewidth(8,500)
        elif message == '40':
            #down
            print 'down'
            pigpio.set_servo_pulsewidth(7,500)
            pigpio.set_servo_pulsewidth(8,2500)
        elif message == '37':
            #right
            print 'right'
            pigpio.set_servo_pulsewidth(7,1400)
            pigpio.set_servo_pulsewidth(8,1400)
        elif message == '39':
            #right
            print 'left'
            pigpio.set_servo_pulsewidth(7,1800)
            pigpio.set_servo_pulsewidth(8,1800)
        elif message == '32':
            #space
            print 'stop'
            pigpio.set_servo_pulsewidth(7,0)
            pigpio.set_servo_pulsewidth(8,0)
        elif message == '65':
            print 'a'
            #print self.cam_value
            if (self.cam_value < 1800):
                pigpio.set_servo_pulsewidth(24,self.cam_value+100)
                self.cam_value+=100
            else:
                self.cam_value=1800
        elif message == '90':
            print 'z'
            #print self.cam_value
            if (self.cam_value > 1300):
                pigpio.set_servo_pulsewidth(24,self.cam_value+100)
                self.cam_value-=100
            else:
                self.cam_value=1300


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
