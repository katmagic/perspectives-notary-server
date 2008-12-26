// this is just some example code for how to do cryto 
// checks and base64 encoding/decoding in javascript. 
function run_crypto_test() { 

  d_print("Starting crypto test"); 
   try {
   var verifier = Cc["@mozilla.org/security/datasignatureverifier;1"].
                  createInstance(Ci.nsIDataSignatureVerifier);
   var data = ""; 
   for(var i = 0; i < 10; i++) { 
	data += String.fromCharCode(i);
   }
   d_print("data = " + data); 

   var signature  =
"MIGTMA0GCSqGSIb3DQEBBAUAA4GBACYiXpqMbnBHeVcaJmvhilhC62oZtnmcEVsw" +
"ZN8CULZBH1II9wZCtyHYnfEHxAEH4CMC+JWY3hjwaQQHk7lIgUYFW3rURX3Udf0v" +
"86QGmMFS1xjT/95D639yPbG7XmVwogDgCiCxpUrPx2MsrX0x/mlK1hFBoFg3kGyH" +
"xnz1V4SN"; 
/*
"MIGTMA0GCSqGSIb3DQEBBAUAA4GBAJKChfVVAspOodRtr1bW/dLZ2rxsgDqJcYpB" + 
"/0AuIegRqvMdwiXOl1rB7M4e+YHq9OiTnRMqqjl60g1uyJj2LXcS36Uxq3bjG1e8" + 
"W9h+yAuIn1YQv8pXxHrYBhXfSmcQqAeYsXs0vWor7U++drd13HT3BS9YoCN+ibCu" +
"EhkIO/R3";
*/ 

var key = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDJM+BYkDaa5REV0IJtbBVOwKSm" + 
"4gufNMHBHaP7Hr0wqGmEWZm66enNGw5rWPvzf9fcxVoda0sC8GEZoRDDfaG6e4Dj" + 
"71zbci09JQ22ql/JUGpFvK1I4wEKsmokrTHspS2LEdT9rWzkkCIaBuIT2irg0Kys" + 
"yyoLzOnHq09U9htviQIDAQAB" 
        d_print("using signature: " + signature); 
	var result = verifier.verifyData(data, signature, key);
        alert("result = " + result);

	var res = Base64.encode("hello my name is dan"); 
	d_print("encoded = " + res); 
 	var dec = Base64.decode(res); 
	d_print("decoded = " + dec); 
 
     } catch(e) { 
	alert("crypto test threw: " + e); 
     }
     d_print("Done with crypto test"); 

}
