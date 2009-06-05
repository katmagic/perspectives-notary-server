//Global Declarations

var notary_list = (function () {
    var notary_url, notaries;

    notary_url = "https://www.networknotary.org/notary_list.txt";


    notaries = (function () {
        var lines, i, notaries, notary_server, key;

        lines = readLocalFileLines("http_notary_list.txt");
        notaries = [];

        i = 0; 
        while (i < lines.length) {  

            notary_server = { "host" : lines[i] }; 
            i += 1;

            if (i >= lines.length || lines[i].indexOf("BEGIN PUBLIC KEY") === -1) { 
                alert("Perspectives: invalid notary_list.txt file: " + lines[i]); 
                return; 
            }
            i += 1;

            key = ""; 
            while (i < lines.length && lines[i].indexOf("END PUBLIC KEY") === -1) { 
                key += lines[i]; 
                i += 1;
            }

            i += 1; // consume the 'END PUBLIC KEY' line
            notary_server.public_key = key; 
            notaries.push(notary_server);  
        } 

        return notaries;
    }());


    /* Currently disabled and untested.  When ready put into the return
     * object.
     * NOTE: disabling auto-update of the notary list
     * b/c it could allow an attacker with a bogus root 
     * cert to compromise the system.  We should have this
     * update include a signature. */

    function update_notarylist() {
        var request = new XMLHttpRequest();

        request.open("GET", notary_url, true);

        request.onload = {
            handleEvent : function (evt) {
                var psv_id, em, file, text, foStream;

                psv_id = "perspectives@cmu.edu"; 

                em = Components.  classes["@mozilla.org/extensions/manager;1"].
                getService(Components.interfaces.nsIExtensionManager);

                file = em.getInstallLocation(psv_id).
                getItemFile(psv_id, "notary_list.txt");

                text = request.responseText;

                d_print("main", "updating notary list to:"); 
                d_print("main", text);  

                foStream = Components.
                classes["@mozilla.org/network/file-output-stream;1"].
                createInstance(Components.interfaces.nsIFileOutputStream);

                // use 0x02 | 0x10 to open file for appending.
                foStream.init(file, 0x02 | 0x08 | 0x20, 666, 0); 
                foStream.write(text, text.length);
                foStream.close();
            }
        };

        request.onerror = {
            handleEvent : function (evt) {
                d_print("error", "failed to update notary_list.txt");
            }
        };

        try {
            request.send("");

        } catch (e) {
            d_print("error", "error updating notary_list.txt: " + e);
        }
    }

    return {
        getNotaries : function () {
            return notaries;
        }
    };
}());

















