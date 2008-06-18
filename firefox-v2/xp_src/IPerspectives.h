/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IPerspectives.idl
 */

#ifndef __gen_IPerspectives_h__
#define __gen_IPerspectives_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IPerspectives */
#define IPERSPECTIVES_IID_STR "9da3e716-40ea-4aac-ada1-08e65bc72a2f"

#define IPERSPECTIVES_IID \
  {0x9da3e716, 0x40ea, 0x4aac, \
    { 0xad, 0xa1, 0x08, 0xe6, 0x5b, 0xc7, 0x2a, 0x2f }}

class NS_NO_VTABLE NS_SCRIPTABLE IPerspectives : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IPERSPECTIVES_IID)

  /* string do_notary_check (in string service_id, in string fingerprint, in string extension_dir); */
  NS_SCRIPTABLE NS_IMETHOD Do_notary_check(const char *service_id, const char *fingerprint, const char *extension_dir, char **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IPerspectives, IPERSPECTIVES_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IPERSPECTIVES \
  NS_SCRIPTABLE NS_IMETHOD Do_notary_check(const char *service_id, const char *fingerprint, const char *extension_dir, char **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IPERSPECTIVES(_to) \
  NS_SCRIPTABLE NS_IMETHOD Do_notary_check(const char *service_id, const char *fingerprint, const char *extension_dir, char **_retval) { return _to Do_notary_check(service_id, fingerprint, extension_dir, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IPERSPECTIVES(_to) \
  NS_SCRIPTABLE NS_IMETHOD Do_notary_check(const char *service_id, const char *fingerprint, const char *extension_dir, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Do_notary_check(service_id, fingerprint, extension_dir, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IPerspectives
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IPERSPECTIVES

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IPerspectives)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* string do_notary_check (in string service_id, in string fingerprint, in string extension_dir); */
NS_IMETHODIMP _MYCLASS_::Do_notary_check(const char *service_id, const char *fingerprint, const char *extension_dir, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IPerspectives_h__ */
