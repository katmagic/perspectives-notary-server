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

// verifies a signature using the XPCOM 'datasignatureverifier' component.
// since the signature of the notary does not contain the full DER header
// expected by the datasignatureverifier, we also pass in a DER header
// to be prepended to the notary signature.  This DER header also indicates
// the exact signature algorithm (e.g., RSA with MD5) 
PRBool verify_signature_with_header(char *der_header, int der_header_len, 
				 unsigned char* sig, int sig_len,
				 unsigned char* data, int data_len, 
				 char *server_key) { 
    nsresult rv; 
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

    full_sig = (unsigned char*) malloc(sig_len + der_header_len); 
    memcpy(full_sig, der_header, der_header_len); 
    memcpy(full_sig + der_header_len, sig, sig_len);  
    SECItem sig_item;
    sig_item.type = siBuffer;
    sig_item.data = full_sig;
    sig_item.len = sig_len + der_header_len; 
   
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


#define DER_HEADER_LEN 22

PRBool verify_signature(char *buf, int msg_len, char *server_key) { 
    PRBool res; 
    
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
    char der_header_md5[DER_HEADER_LEN] = {    0x30, 0x81, 0xbf, 
	0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
	0x0d, 0x01, 0x01, 0x04, 0x05, 0x00, 0x03, 0x81, 0xad, 0x00 };
    char der_header_sha256[DER_HEADER_LEN] = { 0x30, 0x81, 0xbf, 
	0x30, 0x0a, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
	0x0a, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x03, 0x81, 0xad, 0x00 };
    int sig_len = SIGNATURE_LEN;  
    notary_header *hdr = (notary_header*)buf;
    int data_len = ntohs(hdr->total_len) - sig_len - sizeof(notary_header);
    unsigned char* data = (unsigned char*)(hdr + 1);
    unsigned char *sig = (unsigned char*) (data + data_len);
    DPRINTF(DEBUG_INFO, "msg verify: data_len = %d sig_len = %d \n",
			data_len, sig_len);
    res = verify_signature_with_header(der_header_sha256, DER_HEADER_LEN, sig, 
					sig_len, data, data_len, 
					server_key);
    if(res) { 
      DPRINTF(DEBUG_ERROR, "SHA256 verification succeeded\n"); 
      return res; 
    }
    DPRINTF(DEBUG_ERROR, "SHA256 verification failed\n"); 
    res = verify_signature_with_header(der_header_md5, DER_HEADER_LEN, sig, 
					sig_len, data, data_len, 
					server_key);
    if(!res) { 
      DPRINTF(DEBUG_ERROR, "MD5 verification failed\n"); 
    }
    DPRINTF(DEBUG_ERROR, "MD5 verification succeeded\n"); 
    return res; 
}

