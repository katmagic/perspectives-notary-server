#include "pipnss/nsIDataSignatureVerifier.h"
#include "nsStringAPI.h"

#include "nsXPCOM.h"
#include "nsXPCOM.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"
#include "prprf.h"
#include "prio.h"
#include "prerror.h"
#include "prnetdb.h"
#include "nsEmbedString.h"
#include "nsIX509Cert.h"
#include "nsILocalFile.h"
#include "nsDirectoryServiceDefs.h"
#include "nsDirectoryServiceUtils.h"
#include "nsIPrefService.h"
#include "nsIPrefBranch2.h"
#include "nsMemory.h"
#include "pipnss/nsIDataSignatureVerifier.h"
#include <stdlib.h> 

#if WIN32
#include <winsock2.h> 
#endif 

#include "nsCOMPtr.h"
#include "keythi.h"
#include "seccomon.h"
#include "nssb64.h"
#include "certt.h"
#include "keyhi.h"
#include "cryptohi.h"
#include "secder.h"
#include "common.h"


PRBool verify_signature(char *buf, int msg_len, char *server_key) { 
    nsresult rv; 
    //NOTE: the mozilla signature verification API expects a DER-encoded
    // object that includes information about the signature algorithms
    // used.  This data is not in the openssl generated signature, which
    // is only the signature itself.  This binary array data is the 
    // correct header for the signature algorithm and size that we 
    // currently use: MD5 has with RSA signature, and a length of 172 bytes.
    // If the size of key used by notaries changes, we'll have to change 
    // this as well.  The size is encoded in two places, 0xbf indicates the
    // overall size of the entire DER structure, and 0xad indicates the 
    // size of the DER signature.  
    char der_header[22] = { 0x30, 0x81, 0xbf, 0x30, 0x0d, 0x06, 0x09, 
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x04, 0x05, 
	0x00, 0x03, 0x81, 0xad, 0x00 };
	notary_header *hdr = (notary_header*)buf;
    //FIXME: security issue with taking sig len from outside?  
    int sig_len = SIGNATURE_LEN; 
    int data_len = ntohs(hdr->total_len) - sig_len - sizeof(notary_header);
    unsigned char* data = (unsigned char*)(hdr + 1);
    unsigned char *sig = (unsigned char*) (data + data_len);
    unsigned char *full_sig = NULL;
    char *sig64 = NULL; 
    int b64_len = 0; 
    nsEmbedCString sig_str, data_str, key_str; 
    PRBool ret = PR_FALSE; 

    nsCOMPtr<nsIDataSignatureVerifier> sigVerifier =
     do_GetService("@mozilla.org/security/datasignatureverifier;1" , &rv);
    
    if (NS_FAILED(rv)) { 
      DPRINTF(DEBUG_ERROR, "failed to load c++ datasignatureverifier\n"); 
      return PR_FALSE;  
    }
    DPRINTF(DEBUG_INFO, "msg verify: data_len = %d sig_len = %d \n",
			data_len, sig_len);

    full_sig = (unsigned char*) malloc(sig_len + 22); 
    memcpy(full_sig, der_header, 22); 
    memcpy(full_sig + 22, sig, sig_len);  
    SECItem sig_item;
    sig_item.type = siBuffer;
    sig_item.data = full_sig;
    sig_item.len = sig_len + 22; 
   
    b64_len = 2 * sig_item.len;  
    sig64 = (char*)malloc(b64_len); 
    if(NSSBase64_EncodeItem(NULL,sig64, b64_len, &sig_item) == NULL) { 
	DPRINTF(DEBUG_ERROR,"failed to base64 encode signature\n");
	goto fail;  
    }
 
    sig_str.Assign(sig64, strlen(sig64));    
    key_str.Assign(server_key, strlen(server_key));    
    data_str.Assign((char*)data, data_len);
     
    rv = sigVerifier->VerifyData(data_str,sig_str,key_str,&ret);   
    
    if (NS_FAILED(rv)) { 
      DPRINTF(DEBUG_ERROR,"Call to XPCOM VerifyData failed\n"); 
      goto fail;  
    }
    return ret;  

    fail:	
    	if(full_sig) free(full_sig); 
	if(sig64) free(sig64); 
	return PR_FALSE; 
} 

