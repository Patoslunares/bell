#import pymongo
import Serialports
import sys
#import glob
import json
import serial
import time
import msvcrt
import zmq

#import serial.tools.list_ports
#from serial import serial 
#myclient = pymongo.MongoClient("mongodb://localhost:27017/")
#mydb = myclient["pruebas"]
#mycol = mydb["posicion"]



ports = Serialports.ValidPorts();
sesnors = []
for port in ports:
	portuse = port
	print port
	for sensor in ports[portuse]:
		sesnors.append(sensor)

arduino = serial.Serial(portuse, baudrate=9600, timeout=1.0)

read = arduino.readline()
time.sleep(5)
key = None

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

key = None
while key != 'q':
    #  Wait for next request from client
    key = msvcrt.getch()

    message = socket.recv()
    print("Received request: %s" % message)

    #  Do some 'work'
    time.sleep(1)

    #  Send reply back to client
    socket.send(b"World")


print read
print sesnors 


#while True:
#    line = arduino.readline()
#    print(line)

#mydict = { "name": "John", "address": "Highway 37" }

#x = mycol.insert_one(mydict