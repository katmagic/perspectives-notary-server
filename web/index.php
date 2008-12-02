
<html> 
<head>
<title> Perpsectives Demo: SSH and SSL Host Key Records </title>  
<link rel="stylesheet" type="text/css" href="http://www.cs.cmu.edu/~perspectives/style.css"
<script type="text/javascript">
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
var pageTracker = _gat._getTracker("UA-5335740-1");
pageTracker._trackPageview();
</script>
</head>
<body> 
<center>
<table width="100%"> 
<tr> 
<td width="25%"> <a href="http://www.cs.cmu.edu/~perspectives/">
<div class="quick_link"> Perspectives Home </div></a> </td>
<td width="25%"> <a href="http://www.cs.cmu.edu/~perspectives/firefox.html">
<div class="quick_link"> Firefox Extension </div></a> </td>
<td width="25%"> <a href="http://www.cs.cmu.edu/~perspectives/openssh.html">
<div class="quick_link"> OpenSSH Client </div></a> </td>
<td width="25%"> <a href="http://moo.cmcl.cs.cmu.edu/perspectives/">
<div class="quick_link"> Web Demo </div></a> </td>
</tr>
</table> 
</center>

<h1> Perpsectives Notary Demo: SSH and SSL Host Key Records </h1> 
<p> This is a simple web interface to query Perspective's overlay
of "network notary" servers.  Network notaries let you see a 
diverse views of the public key(s) used by a network 
service (e.g., SSH or HTTPS) over time.  
</p> 
<p> To learn more about the Perspectives project, see the 
<a href="http://www.cs.cmu.edu/~perspectives/"> main project page </a> .
</p>
<hr> 
<h4> Try your own Notary query </h4> 
<?php

#default 
$host="www.cs.cmu.edu";
$port="443";
$service_type="2"; 


if(isset($_POST['host']) && isset($_POST['port']) && isset($_POST['service_type'])) {
	$host = $_POST['host'];
        $port = $_POST['port'];
        $service_type= $_POST['service_type'];
       
        if (!(ereg('^(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]$)|(([a-zA-Z0-9\-]+\.)+([a-zA-Z\-]+)))$', $host) ))  {
            echo "Sorry, but '$host' does not appear to be a valid hostname (better safe than sorry when it comes to accepting inputs)"; 
            exit; 
        }
        if (!(ereg('^[0-9]+$', $port))) {
            echo "Invalid port = '$port'"; 
            exit; 
        }
        if (!(ereg('^[1-2]$', $service_type))) {
            echo "Invalid service-type = '$service_type'"; 
            exit; 
        }
}
?> 

<div style="padding: 10px;">
    <form method="post" 
   action="http://moo.cmcl.cs.cmu.edu/perspectives/index.php">
  <table cellpadding="5px" > 
  <tr> 
  <td> Host:</td><td> <input type="text" name="host" value="<?php print $host; ?>" size="30" /> </td>
  </tr> 
  <tr>
  <td> Port: </td><td> <input type="text" name="port" value="<?php print $port; ?>" size="5" /> 
  &nbsp; &nbsp; &nbsp; Default port for HTTPS is 443, for SSH 22.<br/></td>
  </tr>
  <tr>
  <td> Protocol: </td> <td>
  <?php
  if($service_type == "1") { 
  ?> 
     <input type="radio" name="service_type" value="2"  > SSL 
     <input type="radio" name="service_type" value="1" checked="1" /> &nbsp; &nbsp; SSH </td>
  <?php
  } else { 
  ?> 
     <input type="radio" name="service_type" value="2" checked="1" > SSL 
     <input type="radio" name="service_type" value="1" /> &nbsp; &nbsp; SSH </td>
  <?php
  }
  ?> 
  </tr>
  <tr> 
  <td id="warning_row">   </td>
  <td> <input value="Get Notary Results" type="submit"/></td>
 </tr> 
 <tr>
  </table> 
  </form>
  <div style="clear: both;"/>
</div>
  <hr/>

        <h3> Results for <?php print $host . ":" . $port ?></h3> 
        <ul>
        <li><a href="#10days">10-day key history timeline</a></li> 
        <li><a href="#200days">200-day key history timeline</a></li> 
        <li><a href="#details">Detailed ouput showing all notary data.</a></li> 
        <li><a href="#notes">FAQ</a></li> 
        </ul> 
<?php
        if($service_type == 1 && $port != 22) { 
          echo "Warning: You are using a non-standard port for SSH, did you mean to do that?"; 
        } 
        if($service_type == 2 && $port != 443) { 
          echo "Warning: You are using a non-standard port for HTTPS, did you mean to do that?"; 
        } 

        $service = "$host:$port,$service_type";
        # this code actually queries the notaries three different times,
        # but its the simplest to do form PHP right now
        $details = shell_exec("./full_client notary_list.txt \"$service\""); 

        if (strpos($details,"key") === false) { 
          echo "<p><b> Error: </b> It appears that the parameters you selected "; 
          echo "do not correspond to a reachable server.  Please try again.";
          return; 
        } 

        echo "<a name=\"10days\"/>"; 
        echo "<h4> 10-day Key History </h3>"; 
        $fname10 = str_replace( array(":",","), "_", $service) . "_10.svg"; 
        $ignore = shell_exec("./gen_svg \"$service\" notary_list.txt 10 > images/$fname10"); 
        echo "<p><embed src=\"images/$fname10\" alt=\"browser must support SVG\"/></p>";

        echo "<a name=\"200days\"/>"; 
        echo "<h4> 200-day Key History </h3>"; 
        $fname200 = str_replace( array(":",","), "_", $service) . "_200.svg"; 
        $ignore = shell_exec("./gen_svg \"$service\" notary_list.txt 200 > images/$fname200"); 
        echo "<p><embed src=\"images/$fname200\" alt=\"browser must support SVG\"/></p>";

        echo "<a name=\"details\"/>"; 
        echo "<h4> Notary Result Details </h3>"; 
        echo "<pre>$details</pre>"; 

        $datestr = date("r"); 
        system("echo \"$service @ $datestr \" >> log.txt"); 
?>
<a name="notes" /> 
<h4> Frequently Asked Questions (FAQ) </h4> 
<ol> 
<li> Keys are shown as 128-bit MD5 hashes.  This is identical to the "key fingerprint" that you 
see for unauthenticated keys in SSH.  For HTTPS, Firefox and Safari will 
show you the MD5 fingerprint if you view the details of a certificate. </li> 
<li> Note: If you get results that contain [NULL LIST] that means some servers did not have any
results for your service.  The notary servers do probe "on demand" when you request, but if some
servers did not reply, issue the query again, as the local client may have timed-out before the 
notaries finished probing for the key.  If you continue to get no results and you are sure that the
host is reachable, please contact us.  
</li> 
<li> Notaries only keep history
for services that have been requested in the past, so when you first query a
about a service, there may be no history.
</li>
</ol>
<!--RiteCounter-->
<script type="text/javascript" src="http://www.ritecounter.com/c/23/22042.js"></script>
<noscript><p><a href="http://www.ritecounter.com"><img src="http://www.ritecounter.com/scripts/htmlc.php?id=22042" alt="Simple Invisible Counter" style="border: 0;" /></a></p></noscript>
<!--END RiteCounter-->
</body> 
</html> 
