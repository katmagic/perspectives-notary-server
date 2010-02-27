#!@python_EXEC@

import socket,os
import time
import sys
from subprocess import Popen

MAX_NAME_LEN = 128
SERVICE_TYPE_SSL = 2
SERVICE_TYPE_SSH = 1
MAX_SIMULTANEOUS = 100
SOCKET_TIMEOUT = 1
THROTTLE_TIMEOUT = 60

if len(sys.argv) != 2:
	print >> sys.stderr, "ERROR: usage: <scanner-conf>"
	exit(1)

config = {}
f = open(sys.argv[1])
for line in f:
	try:
		key,value = line.strip().split("=")
		config[key] = value
	except:
		pass


def limitSimultaneousQueries():
	# remove any processes that are no
	# longer active
	for id, p in active.items():
		if p.poll() is not None:
			del active[id]
	return len(active) >= MAX_SIMULTANEOUS

def unthrottleQueries():
	now = time.time()
	while len(throttle_queue) > 0:
		query, start = throttle_queue[0]
		if now - start >= THROTTLE_TIMEOUT :
			throttle_queue.pop(0)
			throttle_set.remove(query)
		else :
			break

active = dict ()
throttle_queue = list ()
throttle_set = set ()


s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
try:
    os.remove(config['new_request_sock'])
except OSError:
    pass
s.bind(config['new_request_sock'])
print >> sys.stderr, "INFO: listening on '%s'" % config['new_request_sock']
s.listen(MAX_SIMULTANEOUS)
s.settimeout(SOCKET_TIMEOUT)

while True:
	
	while limitSimultaneousQueries():
		time.sleep(1)
	unthrottleQueries()
	
	conn = None
	try :
		try :
			
			conn, addr = s.accept()
			conn.settimeout(SOCKET_TIMEOUT)
			service_id = conn.recv(MAX_NAME_LEN + 1)
			conn.close()
			conn = None
			
			if len(service_id) == 0 or service_id[-1] != '\0' :
				print >> sys.stderr, "ERROR: invalid request: %s" % service_id
				continue
			service_id = service_id[0:-1] # remove null byte
			
			service_type_str = service_id.split(",")[1]
			service_type = int(service_id.split(",")[1])
			if service_type == SERVICE_TYPE_SSL:
				cmd = config['ssl_scan_binary']
			elif service_type == SERVICE_TYPE_SSH:
				cmd = config['ssh_scan_binary']
			else:
				print >> sys.stderr, "ERROR: invalid service-type: %s" % service_type
				cmd = None
			
			if cmd:
				if service_id not in active and service_id not in throttle_set:
					p = Popen([cmd, service_id, config['request_finished_sock']])
					active[service_id] = p
					throttle_queue.append((service_id, time.time()))
					throttle_set.add(service_id)
				else :
					# this request is already in progress,
					# or it was already made not too long ago
					# thus we just ignore it
					pass
			
		except socket.timeout, e:
			pass
		except Exception, e:
			print >> sys.stderr, "ERROR: ondemand listener error: %s" % e
			
	finally:
		if conn:
			conn.close()
			conn = None
