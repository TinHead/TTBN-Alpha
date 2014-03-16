from wsgiref.simple_server import make_server
from urlparse import parse_qsl
from os import system

html = """
<html>
<body>
   <img src='http://192.168.1.16:8090/?action=stream'/>
   <form method="get" action="parsing_get.wsgi">
      <p>
         <input type="submit" name="bw" value="Forward">
	 <input type="submit" name="fw" value="Backward">
	 <input type="submit" name="rig" value="Left">
	 <input type="submit" name="lef" value="Right">
 	 <input type="submit" name="st" value="Stop">
      </p>
      </form>
   <p>
      Button: %s<br>
      </p>
   </body>
</html>"""

def application(environ, start_response):

   # Returns a dictionary containing lists as values.
   d = parse_qsl(environ['QUERY_STRING'])

   # In this idiom you must issue a list containing a default value.

   age  = 'xxx'  # Returns the first age value.
   try: 
	if (d[0][0]=="fw"):
		print "Forward"
		system("i2cset -y 1 26 0 0")
        if (d[0][0]=="bw"):
                print "Backward"
		system("i2cset -y 1 26 0 1")
        if (d[0][0]=="lef"):
                print "Left"
		system("i2cset -y 1 26 0 2")
        if (d[0][0]=="rig"):
                print "Right"
		system("i2cset -y 1 26 0 3")
        if (d[0][0]=="st"):
                print "Stop"
		system("i2cset -y 1 26 0 4")
   except IndexError:
	pass
   #hobbies = d.get('hobbies', []) # Returns a list of hobbies.

   # Always escape user input to avoid script injection
   #age = escape(age)
   #hobbies = [escape(hobby) for hobby in hobbies]

   response_body = html % (age or 'Empty')

   status = '200 OK'

   # Now content type is text/html
   response_headers = [('Content-Type', 'text/html'),
                  ('Content-Length', str(len(response_body)))]
   start_response(status, response_headers)

   return [response_body]

httpd = make_server('0.0.0.0', 80, application)
# Now it is serve_forever() in instead of handle_request().
# In Windows you can kill it in the Task Manager (python.exe).
# In Linux a Ctrl-C will do it.
httpd.serve_forever()
