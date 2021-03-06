#!@python_EXEC@

import os
import sys
from subprocess import Popen,PIPE,STDOUT 
import time 

# a simple parallel scanner that implements timeouts.
# note: this scanner must be run in tandem with the 'real'
# C scanner, as the 'ssl_scan' and 'ssh_scan' utilities
# report their values back to that scanner via a unix 
# domain socket.  The reason for this scanner is that there
# seems to be issues probe requests getting lost/timedout
# when requested by the c-scanner. 


def start_probe(sid): 
  host_and_port, service_type = sid.split(",")
  if service_type == "2": 
    first_arg = config['ssl_scan_binary'] 
  elif service_type == "1": 
    first_arg = config['ssh_scan_binary'] 
  else: 
    print >> sys.stderr, "ERROR: invalid service_type for '%s'" % sid
    return  
  return Popen([first_arg,sid, config['request_finished_sock']] , 
			stdout=PIPE, stderr=STDOUT, shell=False)
   
if len(sys.argv) != 5: 
  print >> sys.stderr, "ERROR: usage: <service_id_file> <max simultaneous> <timeout sec> " \
		" <scanner-config> "
  sys.exit(1)

config = {} 

f = open(sys.argv[4])
for line in f: 
	try: 
		key,value = line.strip().split("=") 
		config[key] = value
	except: 
		pass

f = open(sys.argv[1])
to_probe = [ line.rstrip() for line in f ] 

total_count = len(to_probe)
active_sids = {}
done = False
max_sim = int(sys.argv[2])
timeout_sec = int(sys.argv[3]) 
failure_count = 0
start_time = time.time()
print >> sys.stderr, "INFO: *** Starting scan of %s services at %s" % \
    (total_count,time.ctime())
print >> sys.stderr, "INFO: *** Timeout = %s sec  Max-Simultaneous = %s" % \
    (timeout_sec, max_sim) 

while True:
  while( len(active_sids) < max_sim ): 
    l = len(to_probe)
    if (l == 0):
      break
    if (l % 1000 == 0): 
      print >> sys.stderr, "INFO: %s probes remaining" % l
    sid = to_probe.pop()
    active_sids[sid] = (start_probe(sid), time.time()) 

  if(len(active_sids) == 0): 
    break # all done
    
  now = time.time() 
  for sid,(p,t) in active_sids.items():
    code = p.poll()
    if code != None:
      if code != 0: 
        print >> sys.stderr, "WARNING: failed: %s %s" % (sid,code)
        failure_count += 1
      p.wait() # apparently this is needed on FreeBSD?
      del active_sids[sid]
    else:
      run_time = now - t
      if run_time > timeout_sec:
        os.kill(p.pid,9) # p.kill() required python 2.6
  sys.stdout.flush()
  sys.stderr.flush()
  time.sleep(1)

duration = time.time() - start_time
print >> sys.stderr, "INFO: *** Finished scan at %s. Scan took %s seconds" % (time.ctime(), duration) 
print >> sys.stderr, "INFO: *** %s of %s probes failed" % (failure_count, total_count)
