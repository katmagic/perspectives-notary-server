#! /usr/bin/python
import sys;
import re;
import httplib;

nhost = "localhost";
nport = 15217;

resp_regex = re.compile(r"<server>.*</server>", re.DOTALL);
url_regex  = re.compile(r"\'(.*):(\d*),(\d*)\'");

def get_resp (host, port, styp):
    url = "/?host=" + host + "&port=" + port + "&service_type=" + styp;
    con = httplib.HTTPConnection(nhost, nport);
    con.request("GET", url);
    resp = con.getresponse();
    return resp.read();

if len(sys.argv) < 2:
    print "Database File Needed";

filename = sys.argv[1];

file = open(filename);

for line in file:
    m = url_regex.search(line)
    if m:
        try:
            resp = get_resp(m.group(1), m.group(2), m.group(3));
        except Exception as e:
            print type(e);
            print m.group();
            print resp;
        m2 = resp_regex.search(resp);
        if m2 is None: #Invalid response
            print "Failed on :" + m.group();




        
