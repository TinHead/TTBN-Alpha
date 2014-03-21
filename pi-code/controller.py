import wiringpi2 as wpy
from time import sleep
from sys import getsizeof,stdin
from tty import setcbreak

from pprint import pprint
#init i2c with slave 0x03
wpy.wiringPiI2CSetup(3)

packet = bytearray(5)

packet[1]=5
packet[2]=0xf3
packet[3]=0xf2
packet[4]=0x02

pprint(packet[1:])
pprint(len(packet))

def send_packet(data):
	data[0] = 0
	i=0
	while i < len(data):
		pprint("loop: "+str(i)+" data "+str(data[i]))
		wpy.wiringPiI2CWrite(3,data[i])
		i+=1
#send_packet(11)

setcbreak(stdin)
while True:
	value = stdin.read(3)
	print ord(value[2])  


#while 1:
#	send_packet(packet)	
#	sleep(0.1)

