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