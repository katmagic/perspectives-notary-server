import sys
import fileinput
import re

match_new_host = re.compile("Start Host:.*") 
match_key = re.compile(".* key:.*") 
match_timespan_start = re.compile("start:.*")

key_map = {} 
timespan_count_map = {} 

for line in fileinput.input(sys.argv[1]): 
  m = match_new_host.match(line)
  if m:
    arr = line.split("'")
    cur_host = arr[1]
    key_map[cur_host] = set()  
    timespan_count_map[cur_host] = 0 
    
  m = match_key.match(line)
  if m: 
    key_map[cur_host].add(line) 
  m = match_timespan_start.match(line)
  if m: 
    timespan_count_map[cur_host] += 1
  
for k in key_map.keys(): 
  if timespan_count_map[k] > 10: 
    print k.rstrip("\n")
    print "num keys = %s " % len(key_map[k]) 
    print "num timespans = %s " % timespan_count_map[k] 
    print "*" * 60
  
