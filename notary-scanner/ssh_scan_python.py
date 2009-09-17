#!/usr/bin/python

from subprocess import *
import re
import sys
import tempfile 
import os

if len(sys.argv) != 4: 
	print "usage: <service-id> <report-obs-binary> <report-sock-name>"
	exit(1)

dns_and_port = sys.argv[1].split(",")[0]
dns_name, port = dns_and_port.split(":") 
	
fname = tempfile.mktemp()

# this sucks, because for any host that is unreachable, 
# we will try once per key type. 
# Also, if the server uses multiple types of keys, it will only 
# record the first one.  
# We tolerate this for now because the number of ssh machines is 
# small and we plan on phasing it out anyway
for key_type in ("rsa","dsa","rsa1"): 
	fd = open(fname,'w')
	p1 = Popen(["ssh-keyscan", "-t", key_type, "-p", port, dns_name ], 
		stdout=fd, stdin=None, stderr=None)
	p1.wait()
	if p1.returncode != 0: 
		print "error fetching ssh '%s' key for %s" % (key_type,dns_and_port)
		continue

	p2 = Popen(["ssh-keygen","-l","-f", fname], 
		stdin=None, stdout=PIPE, stderr=None)
	output = p2.communicate()[0].strip()

	if p2.returncode != 0: 
		print "error converting ssh %s key for '%s'" % (key_type,dns_and_port)
		continue 

	fp = output.split()[1]
	fp_regex = re.compile("^[a-f0-9]{2}(:([a-f0-9]){2}){15}$")
	if not fp_regex.match(fp): 
		print "invalid fingerprint '%s'" % output
		continue

	p3 = Popen([sys.argv[2],dns_name, port, "1", "ssh-" + key_type, fp, sys.argv[3]])
	p3.wait()

	if p3.returncode != 0: 
		print "Error reporting result to notary-scanner socket for '%s'" \
		% dns_and_port
		exit(1) 
	break 

os.remove(fname)
