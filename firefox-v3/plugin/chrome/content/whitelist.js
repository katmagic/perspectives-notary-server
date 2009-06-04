var whitelist = function() {

    var whitelist = eval(readLocalFile("whitelist.json"));
          
    var obj = { 
        onWhitelist : function(host){
            var length = whitelist.length;

            for(var i = 0; i < length; i++){

                if(whitelist[i] === ""){
                    continue;
                }

                if(host.indexOf(whitelist[i]) >= 0){
                    return true;
                }
            }
            return false;
        }
    };

    return obj;
} ();

