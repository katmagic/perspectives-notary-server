# Echo server program
import socket,os
import time
import sys
from subprocess import Popen

MAX_NAME_LEN = 128
SERVICE_TYPE_SSL = 2
SERVICE_TYPE_SSH = 1
MAX_SIMULTANEOUS = 100

if len(sys.argv) != 2: 
	print "usage: <scanner-conf>"
	exit(1) 

config = {} 
f = open(sys.argv[1])
for line in f: 
	try: 
		key,value = line.strip().split("=") 
		config[key] = value
	except: 
		pass


def limitSimultaneousQueries(active): 
	if len(active) >= MAX_SIMULTANEOUS: 
		# remove any processes that are no 
		# longer active 
		for p in active: 
			if p.poll(): 
				active.remove(p) 
	return len(active) >= MAX_SIMULTANEOUS 

active = [] 


s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
try:
    os.remove(config['new_request_sock'])
except OSError:
    pass
s.bind(config['new_request_sock'])
print "listening on '%s'" % config['new_request_sock']
s.listen(1000)
conn = None
while True: 
	try : 
		conn, addr = s.accept()
    		service_id = conn.recv(MAX_NAME_LEN + 1)[0:-1] # remove null byte
		service_type_str = service_id.split(",")[1]
		service_type = int(service_id.split(",")[1])
		if service_type == SERVICE_TYPE_SSL: 
			cmd = config['ssl_scan_binary']
		elif service_tyep == SERVICE_TYPE_SSH: 
			cmd = config['ssh_scan_binary']
		else: 
			print "invalid service-type: %s" % service_type
			continue
		while limitSimultaneousQueries(active): 
			time.sleep(1)
		p = Popen([cmd, service_id, config['request_finished_sock']])
		active.append(p) 
	except Exception, e: 
		print "ondemand listener error: %s" % e
	finally: 
		if conn: 
			conn.close() 


