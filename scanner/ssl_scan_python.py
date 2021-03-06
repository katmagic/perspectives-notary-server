#!@python_EXEC@

from subprocess import *
import re
import sys

if len(sys.argv) != 4:
	print >> sys.stderr, "ERROR: usage: <service-id> <report-obs-binary> <report-sock-name>"
	exit(1)

dns_and_port = sys.argv[1].split(",")[0]

p1 = Popen(["openssl","s_client","-connect", dns_and_port],
		stdin=file("/dev/null", "r"), stdout=PIPE, stderr=None)
p2 = Popen(["openssl","x509","-fingerprint","-md5", "-noout"],
		stdin=p1.stdout, stdout=PIPE, stderr=None)
output = p2.communicate()[0].strip()
p1.wait()
p2.wait()

if p2.returncode != 0:
	print >> sys.stderr, "ERROR: Could not fetch/decode certificate for '%s'" % dns_and_port
	exit(1)

fp_regex = re.compile("^MD5 Fingerprint=[A-F0-9]{2}(:([A-F0-9]){2}){15}$")
if not fp_regex.match(output):
	print >> sys.stderr, "ERROR: invalid fingerprint '%s'" % output
	exit(1)

fp = output.split("=")[1].lower()
dns_name, port = dns_and_port.split(":")

p3 = Popen([sys.argv[2],dns_name, port, "2", "ssl", fp, sys.argv[3]], stdin=file("/dev/null", "r"), stdout=file("/dev/null", "w"), stderr=None)
p3.wait()

if p3.returncode != 0:
	print >> sys.stderr, "ERROR: Error reporting result to notary-scanner socket for '%s'" \
		% dns_and_port
	exit(1)
