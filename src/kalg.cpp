#include <cstring>
#include "kalg.h"

namespace kalg{

  /* 函数名称：Strstrstr 
   * 函数功能：
   *    查找母串中两个字符串之间的字符串的开始和末尾位置，
   *    并返回检索位置末尾。
   * 参    数：
   *    __IN const char *pSrcStrArg,          母串
   *    __IN colonst char *pStartBaseStrArg,  在母串查找开头为该字符子串
   *    __IN const char *pEndBaseStrArg,      在母串查找末尾为该字符子串
   *    __OUT char *pDestStartStrArg,         在母串查找到的中央字符串开头
   *    __OUT char *pDestEndStrArg            在母串查找到的中央字符串末尾
   * 返    回：
   *    成功    返回被查找到的字符串加“被查找串末尾字符串”长度位置
   *    失败    返回 nullptr
   * */
  inline char *Strstrstr(__IN const char *pSrcStrArg, 
      __IN const char *pStartBaseStrArg, 
      __IN const char *pEndBaseStrArg, 
      __OUT char *pDestStartStrArg, 
      __OUT char *pDestEndStrArg)
  {
    if (nullptr != (pDestStartStrArg = (char *)strstr(pSrcStrArg, pStartBaseStrArg)))
    {
      pDestStartStrArg += strlen(pStartBaseStrArg);
      if (nullptr !=(pDestEndStrArg = (char *)strstr(pDestStartStrArg, pEndBaseStrArg))) 
      {
        return pDestEndStrArg + strlen(pEndBaseStrArg);
      }
      else
      {
        pDestStartStrArg = nullptr;
        return nullptr;
      }
    }
    else 
    {
      return nullptr;
    }
  }

  /* new 一个 Strstrstr */
  char *GetStrstrstr(__IN const char *pSrcStrArg, 
      __IN const char *pStartBaseStrArg, 
      __IN const char *pEndBaseStrArg)
  {
    char *pStart = NULL;
    char *pEnd = NULL;

    if (nullptr == Strstrstr(pSrcStrArg, pStartBaseStrArg, pEndBaseStrArg, pStart, pEnd))
    {
      return nullptr;
    }
    else 
    {
      char *pRet = new char[pStart-pEnd+1];
      memcpy(pRet, pStart, pEnd-pStart);
      pRet[pEnd-pStart] = '\0';
      return pRet;
    }
  }
}
