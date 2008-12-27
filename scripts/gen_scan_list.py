import sys
import os
import re

# This script generates a file of services ids (one per line) 
# by including all services-ids in the notary's database that
# have had a successful probe in the past 'max-stale-days' days.
# If max-stale-days is 0, then all service-ids are included.  


if len(sys.argv) != 4: 
  print "usage: <db_env> <db_name> <max-stale-days>"
  exit(1)

f1 = os.popen("utilities/find_stale_services %s %s %s" % \
	(sys.argv[1],sys.argv[2],sys.argv[3]))

stale_hash = {} 
for s in f1:
	arr = s.split()
	stale_hash[arr[0]] = 1

start_host_regex = re.compile("^Start Host")
f2 = os.popen("utilities/db2file %s %s" % (sys.argv[1], sys.argv[2]))
for line in f2:
	if start_host_regex.search(line): 
		s = line.split("'")[1]
		if s not in stale_hash:
			print s

