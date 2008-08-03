import os
import fileinput
import re
import sys

if len(sys.argv) != 3: 
	print "usage: < db text file > < notary file>" 
	quit()

match_new_host = re.compile("Start Host:.*") 
match_key = re.compile(".* key:.*") 
total_count = 0 
print "<html>" 
key_count = 0 

for line in fileinput.input(sys.argv[1]): 
  m = match_new_host.match(line)
  if m:
    key_count = 0
    arr = line.split("'")
    cur_host = arr[1]
  m = match_key.match(line) 
  if m: 
    key_count += 1
    if key_count == 2: # only draw if there are multiple keys
	print "<p> %s </p>" % cur_host
    	fname_base = cur_host.replace(":","_").replace(",","_")
	fname10 = fname_base + "_10.svg"
    	os.system("../utilities/gen_svg %s %s 10 > %s" % (cur_host,sys.argv[2],fname10))
    	print "<embed src=\"%s\" />" % fname10
	fname100 = fname_base + "_100.svg"
    	os.system("../utilities/gen_svg %s %s 200 > %s" % (cur_host,sys.argv[2],fname100))
    	print "<embed src=\"%s\" />" % fname100
	total_count += 1
	
#  if (total_count == 10): 
#	break 

print "</html>"      
