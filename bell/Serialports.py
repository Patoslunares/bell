import sys
import glob
import json
import serial
import time



# Valida el puerto que esta activo y los sensores que se quieres que se buscan
# Retorna un json
def ValidPorts():
	#Argumentos enviados por el usuario
	argvs = sys.argv

	e = False #excluir
	a = False #agregar
	d = []    #sensores

	#agregar sensor a la lista
	if "-a" in argvs:
		a = True

	#excluir sensor
	if "-e" in argvs:
		e = True

	if a and e:
		print "solo se puede un argumento -a o -e"
		sys.exit()

	if not (a or e):
		print "Ingrese un valor \"-a\" para agregar o \"-e\" para excluir \n mas los nombres se los sensores \nejemplo: -a motors"
		sys.exit()

	#leemos los sensores que se esperan encontrar dentro del argumento 
	flag = False
	for argv in argvs:
		if flag:
			d.append(argv)
		if argv == "-a" or argv == "-e":
			flag = True



	#Valia en que sistema operativo se esta ejecutando el programa y se preparan los puertos
	if sys.platform.startswith('win'):
	    ports = ['COM%s' % (i + 1) for i in range(256)]
	elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
	    # this excludes your current terminal "/dev/tty"
	    ports = glob.glob('/dev/tty[A-Za-z]*')
	elif sys.platform.startswith('darwin'):
	    ports = glob.glob('/dev/tty.*')
	else:
	    raise EnvironmentError('Unsupported platform')

	#Se buscan los puertos que si estan conectados 
	result = []
	for port in ports:
	    try:
	        s = serial.Serial(port)
	        s.close() 
	        result.append(port)
	    except (OSError, serial.SerialException):
	        pass


	ValidPorts= {}

	#Se leen los puertos para saber que sensores se esperan de cada uno
	for res in result:
		line = "";
		print res
		arduino = serial.Serial(res, baudrate=9600, timeout=1.0)
		ValidPorts[res]=[]
		time.sleep(5)
		while line == "" :
			line = arduino.readline()
			sensor = json.loads(line)

			for sensor in sensor["sensors"]:
				if a :
					if sensor in d:
						ValidPorts[res].append(sensor)
				if e :
					print sensor+"\n"
					if not sensor in d:
					    ValidPorts[res].append(sensor)


	#eliminamos los puertos que no contengan ningun sensor
	ports = {}
	for valr in ValidPorts:
		if not(not(ValidPorts[valr])):
			ports[valr] = ValidPorts[valr]

	return ports
