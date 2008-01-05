#ifndef _PSV_H_
#define _PSV_H_

#include "nsIBadCertListener.h"


#define PSV_CONTRACTID "@mozilla.org/nsBadCertListener;1"
#define PSV_CLASSNAME "Perspectives implementation of nsIBadCertListener"
//#define PSV_CID  { 0x5c8fa470, 0xae3c, 0x11db, {0xab, 0xbd, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66} }
#define PSV_CID  { 0x78ecbcad, 0x4fdb, 0x63cc, {0x55, 0x71, 0x7b, 0xd3, 0x8d, 0x53, 0x6d, 0x18} }


/* Header file */
class psvBadCertListener : public nsIBadCertListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIBADCERTLISTENER

  psvBadCertListener();


private:
  ~psvBadCertListener();

protected:
  /* additional members */
};


#endif //_PSV_H_
