
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

function readLocalFile(path){ 

   var em = Components.classes["@mozilla.org/extensions/manager;1"].
         getService(Components.interfaces.nsIExtensionManager);
   var file = em.getInstallLocation(MY_ID).getItemFile(MY_ID, path);
   var istream = Components.classes["@mozilla.org/network/file-input-stream;1"].
                        createInstance(Components.interfaces.nsIFileInputStream);
   istream.init(file, 0x01, 0444, 0);
   istream.QueryInterface(Components.interfaces.nsILineInputStream);

   // read lines into array
   var hasmore;
   var text = "";
   var line = {};
   do {
      hasmore = istream.readLine(line)
      if (line.value.length > 0 && line.value[0] != "#") {
          text += line.value + "\n";
      }
   } while(hasmore);

   istream.close();
   return text;
}







