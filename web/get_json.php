<?php

#default 
$host="www.cs.cmu.edu";
$port="443";
$service_type="2"; 

if(isset($_GET['host']) && isset($_GET['port']) && isset($_GET['service_type'])) {
	$host = $_GET['host'];
        $port = $_GET['port'];
        $service_type= $_GET['service_type'];
       
        if (!(ereg('^(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]$)|(([a-zA-Z0-9\-]+\.)+([a-zA-Z\-]+)))$', $host) ))  {
            header("HTTP/1.0 400 Sorry, but '$host' does not appear to be a valid hostname (better safe than sorry when it comes to accepting inputs)"); 
            exit; 
        }
        if (!(ereg('^[0-9]+$', $port))) {
            header("HTTP/1.0 400 Invalid port = '$port'"); 
            exit; 
        }
        if (!(ereg('^[1-2]$', $service_type))) {
            header("HTTP/1.0 400 Invalid service-type = '$service_type'"); 
            exit; 
        }
}

        header('Content-type: application/json'); 

        $service = "$host:$port,$service_type";
        # this code actually queries the notaries three different times,
        # but its the simplest to do form PHP right now
        $details = shell_exec("./full_client notary_list.txt \"$service\" json");
        echo $details; 
?> 
