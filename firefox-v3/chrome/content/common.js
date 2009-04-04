
String.prototype.trim = function() { return this.replace(/^\s+|\s+$/, ''); };

var d_print_all = false; 

var d_print_flags = { 
	"policy" : false, 
	"query" : false,
	"main" : true,  
	"error" :  true 
}; 

function d_print(flag,line) {
try { 
	if(!d_print_flags[flag] && !d_print_all) 
		return; 
	dump(line); 
	other_cache["debug"] += line;
	try { 
	   Firebug.Console.log(line); 
	} catch(e) { 
	   /* ignore, this will blow up if Firebug is not installed */  
	}
     } catch(e) { 
	alert(e); 
     } 
} 


