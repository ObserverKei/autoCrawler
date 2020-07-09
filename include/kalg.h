#ifndef __KALG_H__
#define __KALG_H__

#define __IN
#define __OUT
#define __INOUT

namespace kalg{
  inline char *Strstrstr(__IN const char *pSrcStrArg, __IN const char *pStartBaseStrArg, __IN const char *pEndBaseStrArg, __OUT char *pDestStartStrArg, __OUT char *pDestEndStrArg);
  char *GetStrstrstr(__IN const char *pSrcStrArg, __const char *pStartBaseStrArg, __IN const char *pEndBaseStrArg);
}

#endif//__KLAG_H__
