<html> 
<head>
<script type="text/javascript" src="client_policy.js"></script>
<script type="text/javascript" src="notary_local.js"></script>
<script type="application/javascript"> 

notary_debug = false; 

old_key = "10:3a:19:85:e1:94:12:63:56:4b:ff:2c:1b:14:ff:c5"; 
new_key = "31:e4:9c:8c:2c:0a:7d:45:71:b0:e0:76:ea:a9:f9:17"; 

try { 
	query_json_notary_proxy(new_key, "www.cs.cmu.edu",443,2); 
} catch(e) { 
	alert("exception: " + e); 
}
</script> 
</head>
foo
