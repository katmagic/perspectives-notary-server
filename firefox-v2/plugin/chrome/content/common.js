
function d_print(line) {
	dump(line); 
	other_cache["debug"] += line;
	try { 
	   Firebug.Console.log(line); 
	} catch(e) { 
	   /* ignore, this will blow up if Firebug is not installed */  
	}
} 


