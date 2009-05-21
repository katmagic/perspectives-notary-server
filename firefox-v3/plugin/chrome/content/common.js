
String.prototype.trim = function() { return this.replace(/^\s+|\s+$/, ''); };

var d_print_all = false; 

var d_print_flags = { 
	"policy" : false, 
	"query" : false,
	"main" : false,  
	"error" :  false 
}; 

function d_print(flag,line) {
try { 
	if(!d_print_flags[flag] && !d_print_all) 
		return; 
	dump(line); 
	try { 
	   Firebug.Console.log(line); // this line works in extensions
	} catch(e) { 
	   /* ignore, this will blow up if Firebug is not installed */  
	}
	try { 
	   console.log(line); // this line works in HTML files
	} catch(e) { 
	   /* ignore, this will blow up if Firebug is not installed */  
	}
     } catch(e) { 
	alert(e); 
     } 
} 

function get_unix_time() { 
	var foo = new Date(); // Generic JS date object
	var unixtime_ms = foo.getTime(); // Returns milliseconds since the epoch
	return parseInt(unixtime_ms / 1000);
}

function SEC2DAY(sec) { return sec / (3600 * 24); }  
function DAY2SEC(day) { return day * (3600 * 24); }  
