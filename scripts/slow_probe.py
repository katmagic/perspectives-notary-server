import os
import sys

# an extremely simple scanner with no parallelism.
# this means that if any of the services listed time out,
# everything will hang on the order of 30 seconds.  Right 
# now I use this scanner only on hosts that have not been
# successfully reached by the normal scanning process.  


if len(sys.argv) != 2: 
  print "usage: <service_id_file>"
  exit(1)

f = open(sys.argv[1])
for line in f:
  line = line.rstrip()
  host_and_port, service_type = line.split(",")
  if service_type == "2": 
    cmd = "bin/ssl_scan s_client -connect %s" % host_and_port
  elif service_type == "1": 
    cmd = "bin/ssh_scan %s" % host_and_port
  else: 
    print "invalid service_type for line '%s'" % line
    continue 
  print "start probe: %s" % line
  os.popen(cmd)
  print "end probe: %s" % line
