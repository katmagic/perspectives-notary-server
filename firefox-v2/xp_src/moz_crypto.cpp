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

#include <stdlib.h> 

#if WIN32
#include <winsock2.h> 
#endif 

#include "nsCOMPtr.h"
//#include "nsString.h"

#include "keythi.h"
#include "seccomon.h"
#include "nssb64.h"
#include "certt.h"
#include "keyhi.h"
#include "cryptohi.h"

#include "common.h"



PRBool VerifyData(unsigned char *data, unsigned int data_len,
                  unsigned char *sig, unsigned int sig_len,
                  char *key64, unsigned int key64_len)

{
    // Allocate an arena to handle the majority of the allocations
    PRArenaPool *arena;
	SECStatus ss;
    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (!arena)
        return false;

    DPRINTF(DEBUG_INFO, "Verify sees key = '%s' \n", key64); 

    // Base 64 decode the key
    SECItem keyItem;
    PORT_Memset(&keyItem, 0, sizeof(SECItem));
    if (!NSSBase64_DecodeBuffer(arena, &keyItem,key64,key64_len)) {
	DPRINTF(DEBUG_ERROR, "bad key b64 decode \n"); 
        PORT_FreeArena(arena, PR_FALSE);
        return false;
    }
    
    // Extract the public key from the data
    CERTSubjectPublicKeyInfo *pki = SECKEY_DecodeDERSubjectPublicKeyInfo(&keyItem);
    if (!pki) {
        PORT_FreeArena(arena, PR_FALSE);
	DPRINTF(DEBUG_ERROR, "bad key DER decode \n"); 
        return false;
    }
    SECKEYPublicKey *publicKey = SECKEY_ExtractPublicKey(pki);
    SECKEY_DestroySubjectPublicKeyInfo(pki);
    pki = nsnull;
    
    if (!publicKey) {
        PORT_FreeArena(arena, PR_FALSE);
	DPRINTF(DEBUG_ERROR, "bad key extract\n"); 
        return false;
    }

    DPRINTF(DEBUG_INFO, "key len = %d \n", publicKey->u.rsa.modulus.len); 
    
   SECItem sig_item;
   sig_item.type = siBuffer;
   sig_item.data = sig;
   sig_item.len = sig_len; 
    
   SECAlgorithmID algID; 
   SECOID_SetAlgorithmID(arena,&algID,SEC_OID_PKCS1_MD5_WITH_RSA_ENCRYPTION,NULL); 

    ss = VFY_VerifyDataWithAlgorithmID(data,
                                       data_len, publicKey,
                                       &sig_item,
									   &algID,
                                       NULL, NULL);
        

    // Clean up remaining objects
    SECKEY_DestroyPublicKey(publicKey);
    PORT_FreeArena(arena, PR_FALSE);

	return(ss == SECSuccess);
}


PRBool verify_signature(char *buf, int msg_len, char *server_key) { 

	notary_header *hdr = (notary_header*)buf;
    int sig_len = ntohs(hdr->sig_len);
    int data_len = ntohs(hdr->total_len) - sig_len - sizeof(notary_header);
    unsigned char* data = (unsigned char*)(hdr + 1);
    unsigned char *sig = (unsigned char*) (data + data_len);
    DPRINTF(DEBUG_INFO, "msg verify: data_len = %d sig_len = %d \n",data_len, sig_len);

    return VerifyData(data, data_len, sig, sig_len, server_key, strlen(server_key)); 
} 


