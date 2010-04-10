
String.prototype.trim = function () { 
    return this.replace(/^\s+|\s+$/, ''); 
};

var d_print_all = false; 

var d_print_flags = { 
	"policy" : false, 
	"query" : false,
	"main" : false,  
	"error" :  false 
}; 

function d_print(flag, line) {

    if (!d_print_flags[flag] && !d_print_all) {
        return; 
    }

    dump(line); 
    try { 
        Firebug.Console.log(line); // this line works in extensions
    } catch (e) { 
        /* ignore, this will blow up if Firebug is not installed */  
    }
    
    try { 
        console.log(line); // this line works in HTML files
    } catch (e) { 
        /* ignore, this will blow up if Firebug is not installed */  
    }

} 

function get_unix_time() { 
    var unixtime_ms = (new Date()).getTime(); // Returns milliseconds since the epoch
    return parseInt(unixtime_ms / 1000);
}

function SEC2DAY(sec) { 
    return sec / (3600 * 24); 
}  

function DAY2SEC(day) { 
    return day * (3600 * 24); 
}  

//Returns an array of lines 
function readLocalFileLines(path){
    var MY_ID = "perspectives@cmu.edu"; 
    var em = Components.classes["@mozilla.org/extensions/manager;1"].getService(Components.interfaces.nsIExtensionManager);
    var file = em.getInstallLocation(MY_ID).getItemFile(MY_ID, path);
    var istream = Components.classes["@mozilla.org/network/file-input-stream;1"].
    createInstance(Components.interfaces.nsIFileInputStream);
    istream.init(file, 0x01, 0444, 0);
    istream.QueryInterface(Components.interfaces.nsILineInputStream);

    // read lines into array
    var hasmore;
    var text = "";
    var line = {};

    var line = {}, lines = [], hasmore;
    do {
        hasmore = istream.readLine(line)
        if (line.value.length > 0 && line.value[0] != "#") 
        lines.push(line.value); 
    } while(hasmore);

    istream.close();

    return lines;
}

function readLocalFile(path){ 
    var arr = readLocalFileLines(path);
    var text = "";

    for (i = 0; i < arr.length; i++){
        text += arr[i] + "\n";
    }

    return text;
}

function getdns() {
	var cls = Components.classes['@mozilla.org/network/dns-service;1'];
        var iface = Components.interfaces.nsIDNSService;
        return cls.getService(iface);
}

var dns = getdns();

function get_ips(hostname) {
    var ips = Array();
    var nsrecord = dns.resolve(hostname, true);

    while (nsrecord && nsrecord.hasMore()) {
        ips[ips.length] = nsrecord.getNextAddrAsString();
    }

    return ips;
}
