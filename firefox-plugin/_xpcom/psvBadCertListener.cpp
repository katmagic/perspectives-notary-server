#include "psvBadCertListener.h"

#include "nsXPCOM.h"
#include "nsServiceManagerUtils.h"
#include "nsComponentManagerUtils.h"
#include "psvIBadCertHandler.h"
#include "prprf.h"
#include "prio.h"
#include "prnetdb.h"
#include "nsStringAPI.h"
#include "nsEmbedString.h"
#include "nsIX509Cert.h"
#include "nsILocalFile.h"
#include "nsDirectoryServiceDefs.h"
#include "nsDirectoryServiceUtils.h"
#include "nsIPrefService.h"
#include "nsIPrefBranch2.h"
#include <stdlib.h>

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include "common.h"
#include "notary_local.h"
#include "notary_util.h"
#include "contact_notary.h"
#include "client_policy.h"


#define TIMEOUT 5
#define NUM_RETRIES 2

#define MAX_STALE_SEC (DAY2SEC(5))  
#define KEY_LEN 16

#define SECPREF_HIGH    0
#define SECPREF_MID     1
#define SECPREF_LOW     2


// note: this value is ignored in the Firefox extension code
unsigned int notary_debug;//


char *get_ext_dir()
{
     nsresult rv;
     PRBool retval = PR_FALSE;
     char *ext_dir = NULL;

     nsCOMPtr<psvIBadCertHandler> psv = do_GetService("@cmu.edu/psvBadCertHandler;1");
     psv->SetExtDir(&retval);
     

     nsCOMPtr<nsIPrefService> prefService =
         do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
     if (NS_FAILED(rv))
         return NULL;

     nsCOMPtr<nsIPrefBranch> prefBranch;
     rv = prefService->GetBranch(nsnull, getter_AddRefs(prefBranch));
     if (NS_FAILED(rv))
         return NULL;

    rv = prefBranch->GetCharPref("perspectives.ext_dir", &ext_dir); 
     if (NS_FAILED(rv))
         return NULL;
    return ext_dir;
}


PRInt32 get_sec_pref()
{
     nsresult rv;
     PRInt32 pref;

     nsCOMPtr<nsIPrefService> prefService =
         do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
     if (NS_FAILED(rv))
         return -1;

     nsCOMPtr<nsIPrefBranch> prefBranch;
     rv = prefService->GetBranch(nsnull, getter_AddRefs(prefBranch));
     if (NS_FAILED(rv))
         return -1;

    rv = prefBranch->GetIntPref("perspectives.secpref", &pref); 
     if (NS_FAILED(rv))
         return -1;
    return pref;


}



char *read_file(char *file_name, int *buf_len)
{
    nsresult rv;
    char *buf = NULL; 

    nsCOMPtr<nsILocalFile> file = do_CreateInstance("@mozilla.org/file/local;1", &rv);
    if (NS_FAILED(rv))
    {
        PR_fprintf(PR_STDERR, "Creating Local File Instance Failed \n");
        return NULL;
    }    
      
    char *ext_dir = get_ext_dir();
    
    if (file && ext_dir) 
    {
        rv = file->InitWithPath(NS_ConvertUTF8toUTF16(ext_dir));
        if (NS_FAILED(rv))
        {
            PR_fprintf(PR_STDERR, "Init With path failed \n");
            return NULL;
        }    
    }
    else
    {
        PR_fprintf(PR_STDERR, "Ext dir is NULL \n");
        return NULL;
    }
    
    nsEmbedCString fileName(file_name); 
    file->AppendNative(fileName); 

    nsCString path;
    file->GetNativePath (path);

    PR_fprintf(PR_STDERR, "File Path %s \n", path.get());



    PRBool exists; 
    rv = file->Exists(&exists); 
    if (NS_FAILED(rv)) 
    {
        PR_fprintf(PR_STDERR, "File doesnt exists \n");
        return NULL; 
    }    



    if (exists)  
    { 
        PRUint32 fs, numread; 
        PRInt64 fileSize; 
        rv = file->GetFileSize(&fileSize); 
        if (NS_FAILED(rv)) 
        {
            PR_fprintf(PR_STDERR, "GetFileSize failed \n");
            return NULL; 
        }

        //Comvert 64 bit to 32 bit
        LL_L2UI(fs, fileSize);  

        FILE* openFile; 
        rv = file->OpenANSIFileDesc("r", &openFile); 
        if (NS_FAILED(rv)) 
        {
            PR_fprintf(PR_STDERR, "OpenANSIFileDesc failed \n");
            return NULL; 
        }    

        buf = (char *)malloc((fs+1) * sizeof(char)); 
        if ( ! buf ) 
        {
            PR_fprintf(PR_STDERR, "Malloc Failed \n");
            return NULL; 
        }

        *buf_len = fread(buf, sizeof( char ), fs, openFile); 
        
        if (*buf_len < 0) 
        {
            PR_fprintf(PR_STDERR, "Read Failed \n");
            free(buf);
            fclose(openFile); 
            return NULL;
        }

        // Close file    
        fclose(openFile); 
    }
    return buf;
}


int set_status(char *info, PRBool status)
{

     nsresult rv;
     if(info == NULL)
     {
        printf("Trying to set Null Info. \n");
        return -1;
     }

     nsCOMPtr<nsIPrefService> prefService =
         do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
     if (NS_FAILED(rv))
         return rv;

     nsCOMPtr<nsIPrefBranch> prefBranch;
     rv = prefService->GetBranch(nsnull, getter_AddRefs(prefBranch));
     if (NS_FAILED(rv))
         return rv;

    prefBranch->SetBoolPref("perspectives.status", status); 
    prefBranch->SetCharPref("perspectives.info", info); 
    
    return 0;
}

PRBool verify_key(SSHNotary *notary, nsIX509Cert *cert, PRInt32 pref )
							
{
    nsString fingerprint;
    float threshold = 0.0;
    cert->GetMd5Fingerprint(fingerprint);
    PRUnichar *fpt = (PRUnichar *) fingerprint.get();
    char *binary_key = (char*)malloc(KEY_LEN); 
    char *hex_key = (char*) NS_LossyConvertUTF16toASCII(fpt).get();
    PR_fprintf(PR_STDERR, "MD5 Finger Print is %s\n", hex_key);
    PRInt32 len_out = hexstr_2_buf(hex_key, binary_key, KEY_LEN); 
    if(len_out != KEY_LEN) {
        printf("error, only read %d key bytes, expected %d \n",
                len_out, KEY_LEN);
        return -1;
    }
    
    
    int quorum_size = get_number_of_notaries(notary);

    quorum_size = (int ) (((float) (0.75 * quorum_size))  + 0.5);

    int status = 0;
    uint32_t diff = get_quorum_duration(notary, binary_key, KEY_LEN, SSH_RSA, 
             quorum_size, MAX_STALE_SEC, &status);

    free(binary_key);
    
    if(status == -1)
    {
        return PR_FALSE;
    }


    switch(pref)
    {
        case SECPREF_HIGH: 
                threshold = 3.0;
                break;
        case SECPREF_MID:        
                threshold = 0.0;
                break;
        case SECPREF_LOW:
        default:
                threshold = 0.0;
                break;
            
    }
    return (SEC2DAY(diff) >= threshold);
}

void get_url(nsIX509Cert *cert, char* url_buf, int max_len)
{
     nsEmbedString commonName;
     cert->GetCommonName (commonName);
     PRUnichar *unichar_cname = (PRUnichar *) commonName.get();
     char *char_cname = (char*) NS_LossyConvertUTF16toASCII(unichar_cname).get();
     strncpy(url_buf, char_cname, max_len); 
     PR_fprintf(PR_STDERR," Common Name : '%s' \n", url_buf);
}

PRBool probe_key( nsIX509Cert *cert,
                  char *url,
                  PRInt32 pref)
{

     char buf[512] = {0};
     char *file_buf = NULL;
     int file_buf_len;
     PRBool result = false;
     char *response = NULL;

     PR_fprintf(PR_STDERR, "probing for url = '%s' \n", url); 
     //PR_fprintf(PR_STDERR,"Confirm Certificate Expired\n");

     SSHNotary *notary = init_ssh_notary();

     file_buf = read_file("notary_list.txt", &file_buf_len);       
    
     if(file_buf == NULL)
     {
         printf("Cannot Open notary_list.txt from Profile Folder \n");
         return result;
     }
     PR_fprintf(PR_STDERR, "Read the config File \n");
    
     load_notary_servers(notary, file_buf, file_buf_len);

     PR_fprintf(PR_STDERR, "Loaded Notary Servers \n");

     snprintf(buf, 512, "%s:443,%d", url, SERVICE_TYPE_SSL);
     fetch_notary_observations(notary, buf, TIMEOUT, NUM_RETRIES);

     print_notary_reply(stderr, notary);

     result = verify_key(notary, cert, pref);
     response = get_notary_reply(notary);
     set_status(response, result);
     free(response);
     free(file_buf); 
   
     return result;
}



NS_IMPL_ISUPPORTS1(psvBadCertListener, nsIBadCertListener)

psvBadCertListener::psvBadCertListener() { /*constructor*/ }

psvBadCertListener::~psvBadCertListener() { /*destructor*/ }

/* boolean confirmMismatchDomain (in nsIInterfaceRequestor socketInfo, in AUTF8String targetURL, in nsIX509Cert cert); */
NS_IMETHODIMP psvBadCertListener::ConfirmMismatchDomain(nsIInterfaceRequestor *socketInfo, 
							const nsACString & targetURL, 
							nsIX509Cert *cert, 
							PRBool *_retval) {
    //nsCOMPtr<psvIBadCertHandler> psv = do_GetService("@cmu.edu/psvBadCertHandler;1");
    //psv->ConfirmMismatchDomain(socketInfo, targetURL, cert, _retval);

     *_retval = PR_TRUE;
    return NS_OK;
}


/* boolean confirmCertExpired (in nsIInterfaceRequestor socketInfo, in nsIX509Cert cert); */
NS_IMETHODIMP psvBadCertListener::ConfirmCertExpired(nsIInterfaceRequestor *socketInfo, 
        nsIX509Cert *cert, 
        PRBool *_retval) {

     //nsCOMPtr<psvIBadCertHandler> psv = do_GetService("@cmu.edu/psvBadCertHandler;1");
    // psv->ConfirmCertExpired(socketInfo, cert, _retval);
     *_retval = PR_TRUE;
     return NS_OK;
}

/* boolean confirmUnknownIssuer (in nsIInterfaceRequestor socketInfo, in nsIX509Cert cert, out short certAddType); */
NS_IMETHODIMP psvBadCertListener::ConfirmUnknownIssuer(nsIInterfaceRequestor *socketInfo, 
        nsIX509Cert *cert, 
        PRInt16 *certAddType, 
        PRBool *_retval) {

    PR_fprintf(PR_STDERR,"Confirm Unknown User\n");

     PRInt32 pref;
     char url_buf[512] = {0};
     nsresult rv;
     PRBool result = false;
     PRBool mask_dialog = PR_FALSE;
    
     *_retval = PR_FALSE;
#if 0
    nsCOMPtr<nsISocketTransport> sock = socketInfo->getInterface("@mozilla.org/network/socket-transport:1");

    printf("Socket is %p \n", sock);
#endif


     get_url(cert, url_buf, 512);
     
     if(url_buf[0] == 0)
     {
         goto non_psv;
     }
     pref = get_sec_pref();
     
     result = probe_key(cert, url_buf, pref);

     if(!result)
     {
         // Failed.
         if(pref == SECPREF_HIGH || pref == SECPREF_MID)
         {
             printf("High/Mid Sec Pref Failure \n");
             *_retval = PR_FALSE;
             mask_dialog = PR_TRUE;
         }
     }
     else
     {
        printf("Bypassing the popups.. \n");
        *_retval = PR_TRUE;
        *certAddType =  ADD_TRUSTED_PERMANENTLY;// ADD_TRUSTED_FOR_SESSION ;
        mask_dialog = PR_TRUE;
     }
     

non_psv:
    if(!mask_dialog)
    {
        nsCOMPtr<psvIBadCertHandler> psv = do_GetService("@cmu.edu/psvBadCertHandler;1");
        psv->ConfirmUnknownIssuer(socketInfo, cert, certAddType, _retval);
    }
    return NS_OK;
}

/* void notifyCrlNextupdate (in nsIInterfaceRequestor socketInfo, in AUTF8String targetURL, in nsIX509Cert cert); */
NS_IMETHODIMP psvBadCertListener::NotifyCrlNextupdate(nsIInterfaceRequestor *socketInfo, 
							const nsACString & targetURL, 
							nsIX509Cert *cert) {
        PR_fprintf(PR_STDERR,"Notify CRL Next Update\n");

	// NotifyCrlNextupdate
	nsCOMPtr<psvIBadCertHandler> psv = do_GetService("@cmu.edu/psvBadCertHandler;1");
	psv->NotifyCrlNextupdate(socketInfo, targetURL, cert);

	return NS_OK;
}

