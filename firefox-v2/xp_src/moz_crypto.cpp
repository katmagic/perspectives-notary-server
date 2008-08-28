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

/*
	const char *key = "MIHKMA0GCSqGSIb3DQEBAQUAA4G4ADCBtAKBrAFiENC/BwZXOfzDOed4Qbvjd/25"
	"MixlCMlRUlfArJAvcjeBRmnY4fdQhi7/VH1qZeTQClegX1FMcuOORD29a4lks12W"
	"iXrh1HxLKxCTkPp5ZLqP8OiNxWqHdEQyinh2ulYFXZHWMlXhlsQKV2T7VsmfS0rL"
	"eukQAWpgGTXhACyZNpOQgjMm1vWEFaIsd2tT59Son7vxyCcaBoFCWv+zRW6kwaoK"
	"i0KgnEHwKwcCAwEAAQ==";
*/
/* 
	key.Assign(
"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDK426erD/H3XtsjvaB5+PJqbhj" 
"Zc9EDI5OCJS8R3FIObJ9ZHJK1TXeaE7JWqt9WUmBWTEFvwS+FI9vWu8058N9CHhD" 
"NyeP6i4LuUYjTURnn7Yw/IgzyIJ2oKsYa32RuxAyteqAWqPT/J63wBixIeCxmysf" 
"awB/zH4KaPiY3vnrzQIDAQAB"); 

	data.Assign("Test data for data signature verifier"); 
 
	signature.Assign( // Key 0, Data 0, MD5 hash algorithm
"MIGTMA0GCSqGSIb3DQEBBAUAA4GBAGGb2QkA8LcA+QZj1SoVFmMpVTd9P5Ac0Rjb" 
"ldouMmngztMV/dxymVKCpknqelhsxTQ/zaqGZ4KKzcIffJa9jXi5XUD8XzDIKcFE" 
"dQvti8oUNDPb6l1ybETI8LKh2ywyBCSZ/Q5BwUeS9nfx+4cAnu9YZf29SGljit+Y" 
"XLPKZ+of");


    nsCOMPtr<nsIDataSignatureVerifier> verifier = 
		do_CreateInstance("@mozilla.org/security/datasignatureverifier;1", &rv);
    if (NS_FAILED(rv))
    {
        PR_fprintf(PR_STDERR, "Failed to create XPCOM DataSignatureVerifier\n");
        return;
    }


	verifier->VerifyData(data,signature,key,&result);
*/ 

/*
SEC_ASN1_MKSUB(SECOID_AlgorithmIDTemplate)

const SEC_ASN1Template CERT_SignatureDataTemplate[] =
{
    { SEC_ASN1_SEQUENCE,
        0, NULL, sizeof(CERTSignedData) },
    { SEC_ASN1_INLINE | SEC_ASN1_XTRN,
        offsetof(CERTSignedData,signatureAlgorithm),
        SEC_ASN1_SUB(SECOID_AlgorithmIDTemplate), },
    { SEC_ASN1_BIT_STRING,
        offsetof(CERTSignedData,signature), },
    { 0, }
};
*/

/*
// base-64 encoding code is from openssh.  thanks!

static const char Base64[] =
         "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char Pad64 = '=';


 int b64_ntop(const unsigned char *src, size_t srclength, char *target, size_t targsize)
 {
         size_t datalength = 0;
         unsigned char input[3];
         unsigned char output[4];
         unsigned int i;
 
         while (2 < srclength) {
                 input[0] = *src++;
                 input[1] = *src++;
                 input[2] = *src++;
                 srclength -= 3;
 
                 output[0] = input[0] >> 2;
                 output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
                 output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
                 output[3] = input[2] & 0x3f;
                 //Assert(output[0] < 64);
                 //Assert(output[1] < 64);
                 //Assert(output[2] < 64);
                 //Assert(output[3] < 64);
			
                 if (datalength + 4 > targsize)
                         return (-1);
                 target[datalength++] = Base64[output[0]];
                 target[datalength++] = Base64[output[1]];
                 target[datalength++] = Base64[output[2]];
                 target[datalength++] = Base64[output[3]];
         }
     
         // Now we worry about padding.
         if (0 != srclength) {
                 // Get what's left. 
                 input[0] = input[1] = input[2] = '\0';
                 for (i = 0; i < srclength; i++)
                         input[i] = *src++;
         
                 output[0] = input[0] >> 2;
                 output[1] = ((input[0] & 0x03) << 4) + (input[1] >> 4);
                 output[2] = ((input[1] & 0x0f) << 2) + (input[2] >> 6);
              // Assert(output[0] < 64);
              // Assert(output[1] < 64);
              // Assert(output[2] < 64);
				  
 
                 if (datalength + 4 > targsize)
                         return (-1);
                 target[datalength++] = Base64[output[0]];
                 target[datalength++] = Base64[output[1]];
                 if (srclength == 1)
                         target[datalength++] = Pad64;
                 else
                         target[datalength++] = Base64[output[2]];
                 target[datalength++] = Pad64;
         }
         if (datalength >= targsize)
                return (-1);
         target[datalength] = '\0';      // Returned value doesn't count \0. 
         return (datalength); 
 }


 // caller must free returned buffer
 char* get_base64(const unsigned char *data, unsigned int len)
 {
 	char *buf;
 	int n; //, i; 
 
 	if (len > (1 << 24)) {
 		printf("get_base64 got huge size = %d\n", len);
 		return NULL;
 	}
 	buf = (char*)malloc(2*len);
 	n = b64_ntop(data, len, buf, 2*len);

	return buf;
}

*/

