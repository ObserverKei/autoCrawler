#include "public.h"
#include "spider.h"

int main(int argc, const char *argv[])
{
  FILE *fpDownloadList = NULL;
  char *pTmpBuff = new char[__SPIDER_STR_LEN_4096__];
  vector<Spider<SPIDER_DOWNLOAD_DATA_S *> *> spiderList;
  bool complete = false;
  
  sprintf(pTmpBuff, "%sdownload.txt", __DOWNLOAD_PATH__);
  fpDownloadList = fopen(pTmpBuff, "r");

  while (NULL != (fgets(pTmpBuff, __SPIDER_STR_LEN_4096__, fpDownloadList)))
  {
    if ('\n' == pTmpBuff[strlen(pTmpBuff)-1])
    {
      pTmpBuff[strlen(pTmpBuff)-1] = '\0';
    }
    if (strlen(pTmpBuff) > 0)
    {
      spiderList.push_back(new Spider<SPIDER_DOWNLOAD_DATA_S *>(new SPIDER_DOWNLOAD_DATA_S{
              .url = pTmpBuff,
              }));
      pTmpBuff = new char[__SPIDER_STR_LEN_4096__]{0};
    }
  }

  while (!complete) 
  {
    complete = true;
    for (int i = 0; i < spiderList.size(); ++i) 
    {
      if (spiderList[i]->Work()) 
      {
        complete = false;
      }
    }
  }

  for (int i = 0; i < spiderList.size(); ++i) 
  {
    delete spiderList[i];
    spiderList[i] = nullptr;
  }

	return 0;
}
