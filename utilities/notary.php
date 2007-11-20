<?php

$file = "1000_hosts.txt";

$fh = fopen($file,"r");

while ($line = fgets($fh)) {
 
  //$arr = explode(':', $line);
  $test = rtrim($line);
  if (!(ereg('^(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+\:[0-9]+)|([a-zA-Z0-9\-]+\.)+([a-zA-Z\-]+\:[0-9]+))$'
          , $test) )) 
    print "failed : '" . $test . "'\n";
}

fclose($fh);

?>
