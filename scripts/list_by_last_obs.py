#!@python_EXEC@

import sys
import os
import re
import time

# This script generates a file of services id / date pairs
# indicating when the last time the notary successfully observed
# a key from that service.  The first two parameters point to the
# notary's database and are passed on to 'db2file'.  The last two
# parameters filter the set of service ids printed based on the
# last observation date.  If 'newer'' is provided, the script will
# only print services with an observation newer than 'days' days.
# If 'older' is provided, the script will print only service ids
# with a MOST RECENT observation that is older than 'days' days.
# Thus, the script can be used to either generate a list of all services
# considered 'live' and of all services considered 'dead'.

def print_line():
	print "%s %s" % (service_id,time.ctime(most_recent_ts))

def print_if_valid():
	if service_id != None:
		if is_older and most_recent_ts < threshold_date:
			print_line()
		elif not is_older and most_recent_ts > threshold_date:
			print_line()


if len(sys.argv) != 5:
  print "usage: <db_env> <db_name> <older|newer> <days>"
  exit(1)

threshold_date = time.time() - 3600 * 24 * int(sys.argv[4])

is_older = True
if sys.argv[3] == "newer":
	is_older = False

start_host_regex = re.compile("^Start Host")
end_ts_regex = re.compile("^end:")
service_id = None


f2 = os.popen("@notary_bin_PATH@/@notary_bin_PREFIX@db2file %s %s" % (sys.argv[1], sys.argv[2]))

for line in f2:
	if start_host_regex.search(line):
		# do processing for service-id that is now finished
		# start tracking new service-id
		print_if_valid()
		most_recent_ts = 0
		service_id = line.split("'")[1]
	if end_ts_regex.search(line):
		ts = int(line.split()[1])
		if (ts > most_recent_ts):
			most_recent_ts = ts

# catch the last service-id
print_if_valid()
