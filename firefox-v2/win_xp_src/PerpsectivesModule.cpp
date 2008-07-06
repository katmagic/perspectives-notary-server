#include "nsIGenericFactory.h"
#include "Perspectives.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(Perspectives)

static nsModuleComponentInfo components[] =
{
    {
       PERSPECTIVES_CLASSNAME, 
       PERSPECTIVES_CID,
       PERSPECTIVES_CONTRACTID,
       PerspectivesConstructor,
    }
};

NS_IMPL_NSGETMODULE("PerspectivesModule", components) 