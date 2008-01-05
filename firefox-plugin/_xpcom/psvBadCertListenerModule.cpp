#include "nsIGenericFactory.h"
#include "psvBadCertListener.h"

#include "nsStringAPI.h"
#include "nsXPCOM.h"
#include "nsServiceManagerUtils.h"
#include "nsILocalFile.h"
#include "nsDirectoryServiceDefs.h"
#include "nsDirectoryServiceUtils.h"
#include <stdlib.h> //debug
#include <stdio.h> //debug

NS_GENERIC_FACTORY_CONSTRUCTOR(psvBadCertListener)

static NS_METHOD psvBadCertListenerRegister(nsIComponentManager *aCompMgr,
    nsIFile *aPath, const char *registryLocation, const char *componentType,  
    const nsModuleComponentInfo* info)
{
    fprintf(stderr, "Registering.. \n");
    
    nsCOMPtr<nsILocalFile> localFile = do_QueryInterface(aPath); 
    if (!localFile) 
    {
        fprintf(stderr, "do_QueryInterface failed \n");
        return NS_OK; 
    }

    nsCString path_str;
    localFile->GetNativePath (path_str);

    fprintf(stderr, "Path is %s \n", path_str.get());

    return NS_OK;
}

static NS_METHOD psvBadCertListenerUnregister(nsIComponentManager *aCompMgr,
        nsIFile *aPath, const char *registryLocation,
        const nsModuleComponentInfo* info)
{

    fprintf(stderr, "UnRegistering.. \n");
    return NS_OK;
}



static nsModuleComponentInfo components[] =
{
    {
       PSV_CLASSNAME, 
       PSV_CID,
       PSV_CONTRACTID,
       psvBadCertListenerConstructor,
       psvBadCertListenerRegister,
       psvBadCertListenerUnregister
    }
};

NS_IMPL_NSGETMODULE("psvBadCertListenerModule", components) 

