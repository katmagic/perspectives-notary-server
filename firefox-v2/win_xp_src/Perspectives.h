#ifndef _PERSPECTIVES_H_
#define _PERSPECTIVES_H_

#include "IPerspectives.h"

#define PERSPECTIVES_CONTRACTID "@cs.cmu.edu/Perspectives;1"
#define PERSPECTIVES_CLASSNAME "Perspectives HTTPS Certificate Validation"
#define PERSPECTIVES_CID  { 0xe2be5562, 0x61c4, 0x4e8d, { 0xa9, 0x8d, 0x59, 0xd2, 0xb9, 0x85, 0xed, 0xa6 } }

/* Header file */
class Perspectives : public IPerspectives
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IPERSPECTIVES

  Perspectives();
  virtual ~Perspectives();
  /* additional members */
};


#endif //_PERSPECTIVES_H_
