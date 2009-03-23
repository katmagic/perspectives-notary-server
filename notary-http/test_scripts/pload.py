#First argument is the number of threads
#Second argument is the number of connections per second (ish)

import threading;
import httplib;
import time;
import sys;
import string;

nhost = "eblack.res.cmu.edu";
nport = 15217;
url   = '/?host=moo.cmcl.cs.cmu.edu&port=443&service_type=2';

def pnumloop (num):
    print "New Thread";
    while 1:
        for i in range(num):
            con = httplib.HTTPConnection(nhost, nport);
            con.request("GET", url);
            resp = con.getresponse();
            con.close();
        time.sleep(1);

nthrd = int(sys.argv[1]);
ncon  = int(sys.argv[2]);

print nthrd;
print ncon;

tlist = [];
for i in range(nthrd):
    tmp_thread = threading.Thread(None, pnumloop, None, (ncon,));
    tmp_thread.start();
    print i + 1;
    tlist.append(tmp_thread);


raw_input();
sys.exit(0);

