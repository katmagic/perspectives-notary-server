#include "Perspectives.h"
#include <stdlib.h> 
#include <stdio.h>

#if WIN32
#include <Winsock2.h>
#endif


// XPCOM headers copied from old version of the component
// We probably don't need them all, but i'm i'm too lazy to 
// figure out which ones we can delete. 
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


#include "contact_notary.h"

extern "C" { 
#include "common.h" 
#include "notary_local.h"
#include "notary_util.h"
#include "client_policy.h" 
} 



#define TIMEOUT 5
#define NUM_RETRIES 2

#define MAX_STALE_SEC (DAY2SEC(5))  
#define KEY_LEN 16



// TODO: put these helper functions in a utility class 


char *read_file(const char *ext_dir, const char *file_name, int *buf_len){
    nsresult rv;
    char *buf = NULL; 

    nsCOMPtr<nsILocalFile> file = do_CreateInstance("@mozilla.org/file/local;1", &rv);
    if (NS_FAILED(rv))
    {
        PR_fprintf(PR_STDERR, "Creating Local File Instance Failed \n");
        return NULL;
    }    
      
    
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
        PRUint32 fs; // , numread; 
        PRInt64 fileSize; 
        rv = file->GetFileSize(&fileSize); 
        if (NS_FAILED(rv)) 
        {
            PR_fprintf(PR_STDERR, "GetFileSize failed \n");
            return NULL; 
        }

        //Convert 64 bit to 32 bit
        LL_L2UI(fs, fileSize);  

		PRFileDesc *fd;
		nsresult rv = file->OpenNSPRFileDesc(PR_RDONLY, 0, &fd);
        if (NS_FAILED(rv)) 
        {
            PR_fprintf(PR_STDERR, "OpenNSPRFileDesc failed \n");
            return NULL; 
        }

        buf = (char *)malloc((fs+1) * sizeof(char)); 
        if ( ! buf ) 
        {
            PR_fprintf(PR_STDERR, "Malloc Failed \n");
            return NULL; 
        }

		PRInt32 n, so_far = 0;
   
		while ((n = PR_Read(fd, buf + so_far, fs - so_far)) > 0)
		{
			so_far += n; 
		}

		*buf_len = so_far; 
		if (n < 0) 
			PR_fprintf(PR_STDERR, "Error reading file: %d\n", (int)PR_GetError());
		 
		PR_Close(fd);

    }
    return buf;
}


int set_status(char *info, char *svg, double qd_days, PRBool is_cur_consistent)
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

    char buf[32];
    snprintf(buf,32,"%.2f", qd_days);
    prefBranch->SetCharPref("perspectives.quorum_duration", buf); 
    prefBranch->SetBoolPref("perspectives.is_consistent", is_cur_consistent); 
    prefBranch->SetCharPref("perspectives.info", info); 
	prefBranch->SetCharPref("perspectives.svg", svg);
    return 0;  
}



unsigned int notary_debug = DEBUG_ERROR | DEBUG_INFO | DEBUG_POLICY; 

NS_IMPL_ISUPPORTS1(Perspectives, IPerspectives)

Perspectives::Perspectives()
{
  /* member initializers and constructor code */
}

Perspectives::~Perspectives()
{
  /* destructor code */
}


/* string do_notary_check (in string service_id, in string fingerprint); */
NS_IMETHODIMP Perspectives::Do_notary_check(const char *service_id, 
	const char *fingerprint, const char *local_dir, char **_retval)
{
    char *file_buf = NULL;
    int file_buf_len; 
    PRBool result = false; 
    char *response = NULL; 
   

	const char myResult[] = "";
    if(!_retval) return NS_ERROR_NULL_POINTER;

    *_retval = (char*) nsMemory::Clone(myResult, 
                                       sizeof(char)*(strlen(myResult)+1));

    char *host = strdup(service_id); 
    char *colon = strchr(host,':'); 
    if(colon)
 	*colon = 0; // get just host portion of the string 


 /* have not yet ported is_rfc1918 to WIN32
    if(is_rfc1918(host)) { 
	char buf[255]; 
     	snprintf(buf,255,"Did not query notaries because client supplied" 
		    " a RFC 1918 private address: %s \n", host);  
	set_status(buf, 0.0, 0);
	printf("skipping probing because of RFC 1918 address: %s \n", host); 
	free(host); 
    	return NS_OK; 
    }  
*/
    free(host); 
    DPRINTF(DEBUG_INFO,"Perspectives received service_id = '%s' and fingerprint = '%s'\n",service_id, fingerprint);

    SSHNotary *notary = init_ssh_notary(); 
    file_buf = read_file(local_dir, "notary_list.txt", &file_buf_len);       

    if(file_buf == NULL)
    {
	    PR_fprintf(PR_STDERR,"Cannot Open notary_list.txt from Profile Folder \n");
	    return result;
    }	
    DPRINTF(DEBUG_INFO, "Read %d bytes from notary_list.txt \n", file_buf_len);

    load_notary_servers(notary, file_buf, file_buf_len);

    DPRINTF(DEBUG_INFO, "Loaded Notary Servers from file \n");

    fetch_notary_observations(notary, (char*)service_id, TIMEOUT, NUM_RETRIES);

    print_notary_reply(stderr, notary);

    DPRINTF(DEBUG_INFO, "MD5 Finger Print is %s\n", fingerprint);

	char *binary_key = (char*)malloc(KEY_LEN); 
    PRInt32 len_out = hexstr_2_buf((char*)fingerprint, binary_key, KEY_LEN); 
    if(len_out != KEY_LEN) {
        PR_fprintf(PR_STDERR,"error, only read %d key bytes, expected %d \n",
                len_out, KEY_LEN);
        return NS_OK;
    }
 
	nsresult rv;

    nsCOMPtr<nsIPrefService> prefService =
      do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
    if (NS_FAILED(rv)){
      return rv;
    }

    nsCOMPtr<nsIPrefBranch> prefBranch;
    rv = prefService->GetBranch(nsnull, getter_AddRefs(prefBranch));
    if (NS_FAILED(rv)){
      return rv;
    }
    int ret = 0;
    prefBranch->GetIntPref("perspectives.quorum_thresh", &ret);

	float quorum_percent = .01 * (float)ret; 
	DPRINTF(DEBUG_POLICY,"quorum_percent = %f \n", quorum_percent); 
    float quorum_size = (int)(quorum_percent * (float)notary->num_servers + 0.5);

    DPRINTF(DEBUG_POLICY,"Using Quorum Size %f\n", quorum_size);
    PRBool is_cur_consistent; 


    PRUint32 quorum_duration = get_quorum_duration(notary, binary_key, 
        KEY_LEN, SSL_ANY, quorum_size, MAX_STALE_SEC, &is_cur_consistent);

    free(binary_key);
    char *svg = get_reply_as_svg(service_id, notary, 30);

    double qd_days = SEC2DAY(quorum_duration); 
    DPRINTF(DEBUG_POLICY, "QD = %f days \n", qd_days);

     // get text of notary response
     response = get_reply_as_text(notary);
	 DPRINTF(DEBUG_INFO,"Response:\n%s", response); 
     int res = set_status(response, svg, qd_days, is_cur_consistent);
     if(res) { 
		PR_fprintf(PR_STDERR, "Error setting status \n"); 
     } 

     free(response);
     free(file_buf); 

     return *_retval ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}

