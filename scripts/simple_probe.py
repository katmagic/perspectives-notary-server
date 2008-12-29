import os
import sys
from subprocess import * 
import time 

# an extremely simple scanner with no parallelism.
# this means that if any of the services listed time out,
# everything will hang on the order of 30 seconds.  Right 
# now I use this scanner only on hosts that have not been
# successfully reached by the normal scanning process.  


def start_probe(sid): 
  host_and_port, service_type = sid.split(",")
  if service_type == "2": 
    cmd = "bin/ssl_scan s_client -connect %s" % host_and_port
  elif service_type == "1": 
    cmd = "bin/ssh_scan %s" % host_and_port
  else: 
    print "invalid service_type for '%s'" % sid
    return  
  return Popen(cmd, stdout=PIPE, stderr=STDOUT, shell=True)
   

if len(sys.argv) != 3: 
  print "usage: <service_id_file> <max simultaneous>"
  exit(1)

f = open(sys.argv[1])
to_probe = [ line.rstrip() for line in f ] 

active_sids = {}
done = False
max_sim = int(sys.argv[2])

while not done:
  while( len(active_sids) < max_sim ): 
    if (len(to_probe) == 0):
      break
    sid = to_probe.pop()
    active_sids[sid] = start_probe(sid)

  if(len(active_sids) == 0): 
    break # all done
    
  for sid,p in active_sids.items():
    if p.poll() != None:
      code = p.poll()
      if code != 8: 
        print "'%s' exited with error code '%s'" % (sid,code)
      del active_sids[sid]
  time.sleep(1)
