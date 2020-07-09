#ifndef __SPIDER_H__
#define __SPIDER_H__

#include "public.h"
#include "https.h"

struct SPIDER_DOWNLOAD_DATA_S;
template <typename D> class Spider;
template <typename D> using WORK_FUNCTION_T = void *(*)(D, Spider<D> *);

struct SPIDER_DOWNLOAD_DATA_S {
  char *url;
  char *dirPath;
  struct {
    char *start;
    char *end;
    struct {
      char *start;
      char *end;
    }toPageHtmlRule;
  }homeHtmlToPageHtmlRule;
  void Destroy(void) {
    if (nullptr != url) 
    {
      delete[] url;
      url = nullptr;
    }
    if (nullptr != dirPath)
    {
      delete[] dirPath;
      dirPath = nullptr;
    }
    if (nullptr != homeHtmlToPageHtmlRule.start)
    {
      delete[] homeHtmlToPageHtmlRule.start;
      homeHtmlToPageHtmlRule.start = nullptr;
    }
    if (nullptr != homeHtmlToPageHtmlRule.end)
    {
      delete[] homeHtmlToPageHtmlRule.end;
      homeHtmlToPageHtmlRule.end = nullptr;
    }
    if (nullptr != homeHtmlToPageHtmlRule.toPageHtmlRule.start)
    {
      delete[] homeHtmlToPageHtmlRule.toPageHtmlRule.start;
      homeHtmlToPageHtmlRule.toPageHtmlRule.start = nullptr;
    }
    if (nullptr != homeHtmlToPageHtmlRule.toPageHtmlRule.end)
    {
      delete[] homeHtmlToPageHtmlRule.toPageHtmlRule.end;
      homeHtmlToPageHtmlRule.toPageHtmlRule.end = nullptr;
    }
  }
};


template<typename D>
class Spider {
	public:
    Spider(const char *data); 
    Spider(SPIDER_DOWNLOAD_DATA_S *data);
    ~Spider();
    bool Work();
    inline bool LoadDownloadConfig();
    bool LoadDownloadConfig(SPIDER_DOWNLOAD_DATA_S *pDataArg);
    inline bool SpiderDataDestory();
    bool SpiderDataDestory(SPIDER_DOWNLOAD_DATA_S *data);
    bool SpiderDataDestory(const char *data);
    static void *HttpUrlToHomeHtml(__IN const char *data, __IN Spider<const char *> *pThis);
    static void *HttpUrlToHomeHtml(__IN SPIDER_DOWNLOAD_DATA_S *data, __IN Spider<SPIDER_DOWNLOAD_DATA_S *> *pThis);
    static void *HttpHomeHtmlToPageHtml(__IN const char *data, __INOUT Spider<const char *> *pThis);
    static void *HttpHomeHtmlToPageHtml(__IN SPIDER_DOWNLOAD_DATA_S *data, __INOUT Spider<SPIDER_DOWNLOAD_DATA_S *> *pThis);  
    static const char *UrlToHtml(__IN const char *pUrlArg, __IN const char *savePath, __IN const char *saveFilename);

  private:
    int m_workFlag;
    D m_data;
    queue<pair<D, WORK_FUNCTION_T<D> > > *m_workList;
};

  template <typename D>
Spider<D>::Spider(const char *data) : m_workFlag(0),
  m_data(data),
  m_workList(new queue<pair<D, WORK_FUNCTION_T<D> > >)
{
  m_workList->push(pair<D, WORK_FUNCTION_T<D> >(data, HttpUrlToHomeHtml));
}

  template <typename D>
Spider<D>::Spider(SPIDER_DOWNLOAD_DATA_S *data) : m_workFlag(0),
  m_data(data),
  m_workList(new queue<pair<D, WORK_FUNCTION_T<D> > >)
{
  if (true == LoadDownloadConfig())
  {
    printf("url:%s\n", m_data->url);
    printf("dirPath:%s\n", m_data->dirPath);
    printf("home:start:%s\n", m_data->homeHtmlToPageHtmlRule.start);
    printf("home:end:%s\n", m_data->homeHtmlToPageHtmlRule.end);
    printf("home:toPage:start:%s\n", m_data->homeHtmlToPageHtmlRule.toPageHtmlRule.start);
    printf("home:toPage:end:%s\n", m_data->homeHtmlToPageHtmlRule.toPageHtmlRule.end);

  }
  m_workList->push(pair<D, WORK_FUNCTION_T<D> >(data, HttpUrlToHomeHtml));
}
 
  template<typename D>
inline bool Spider<D>::SpiderDataDestory(void)
{
  return SpiderDataDestory(m_data);
}

  template<typename D>
bool Spider<D>::SpiderDataDestory(SPIDER_DOWNLOAD_DATA_S *pDataArg)
{
  puts("开始删除数据");
  if (nullptr != m_data)
  {
    m_data->Destroy();
    m_data = nullptr;
  }
  puts("删除数据成功");
  return true;
}
  template <typename D>
bool Spider<D>::SpiderDataDestory(const char *pDataArg)
{
  delete[] m_data;
  m_data = nullptr;
  return true;
}

  template <typename D>
Spider<D>::~Spider()
{

} 

	template <typename D>
bool Spider<D>::Work(void) 
{
	if (m_workList == nullptr)
	{
		return false;
	}

  printf("work in\n");
	m_workList->front().second(m_workList->front().first, this);
	m_workList->pop();
  if (0 == m_workList->size())
  {
    printf("delete success\n");
    SpiderDataDestory();
    m_workList = nullptr;
  }
  printf("work out\n");

	return true;
}

  template <typename D>
inline bool Spider<D>::LoadDownloadConfig(void)
{
  return LoadDownloadConfig(m_data);
}

  template <typename D> 
bool Spider<D>::LoadDownloadConfig(SPIDER_DOWNLOAD_DATA_S *pDataArg)
{
	char pTmpBuff[__SPIDER_STR_LEN_2048__] = {0};
	const char *pTmpCh = NULL;
	char pTmpName[__SPIDER_STR_LEN_64__] = {0};
  FILE *fpConfig = NULL;
	int base = 0;
  int i = 0;
  bool find = false;
  const char *pStart = NULL;
  const char *pEnd = NULL;
	
	if (NULL == (pTmpCh = strstr(pDataArg->url, "//")))
	{
    base = 0;
	}
	else
	{
    base = pTmpCh + strlen("//") - pDataArg->url;
	}
	if (NULL == (pTmpCh = strstr(pDataArg->url + base, "/")))
  {
    pTmpCh = pDataArg->url + strlen(pDataArg->url);
  }
	for (i = 0; i < (pTmpCh - (pDataArg->url + base)); ++i)
	{
    pTmpName[i] = pDataArg->url[base + i];
	}
	pTmpName[i] = '\0';

	if ((strlen(__DOWNLOAD_PATH__) + strlen(pTmpName)) > sizeof(pTmpBuff))
	{
    fprintf(stderr, "fail to create dir name of HttpHomeHtmlToPageHtml\n");
    return false;
	}
	sprintf(pTmpBuff, "%s%s/", __DOWNLOAD_PATH__, pTmpName);

  pDataArg->dirPath = new char[strlen(pTmpBuff)+1];
  strcpy(pDataArg->dirPath, pTmpBuff);

  sprintf(pTmpBuff, "%sconfig.json", __DOWNLOAD_PATH__);
  if (NULL == (fpConfig = fopen(pTmpBuff, "r")))
  {
    fprintf(stderr, "fail to open in LoadDownloadConfig: %s\n", pTmpBuff);
    return false;
  }

  while (NULL != (fgets(pTmpBuff, sizeof(pTmpBuff), fpConfig)))
  {
    if (!find)
    {
      if (NULL != strstr(pTmpBuff, pDataArg->url))
      {
        find = true;
        i = 0;
      }
    }
    else
    {
      switch (++i)
      {
        case 1:{  /* dirPath */
                 break;
               }
        case 2:{  /* homeHtmlToPageHtmlRule */
                 break;
               }
        case 3:{  /* start */
                 if (nullptr == (pDataArg->homeHtmlToPageHtmlRule.start = GetStrstrstr(pTmpBuff, 
                         "\"start\":\"", 
                         "\",")))
                 {
                   fprintf(stderr, "fail to Strstrstr %s\n", pDataArg->dirPath);
                   return false;
                 }
                 break;
               }
        case 4:{  /* end */
                 if (nullptr == (pDataArg->homeHtmlToPageHtmlRule.end = GetStrstrstr(pTmpBuff, 
                         "\"end\":\"", 
                         "\",")))
                 {
                   fprintf(stderr, "fail to Strstrstr %s\n", pDataArg->dirPath);
                   return false;
                 }
                 break;
               }
        case 5:{  /* toPageHtmlRule */
                 break;
               }
        case 6:{  /* start */
                 if (nullptr == (pDataArg->homeHtmlToPageHtmlRule.toPageHtmlRule.start = GetStrstrstr(pTmpBuff, 
                         "\"start\":\"", 
                         "\",")))
                 {
                   fprintf(stderr, "fail to Strstrstr %s\n", pDataArg->dirPath);
                   return false;
                 }
                 break;
               }
        case 7:{  /* end */
                 if (nullptr == (pDataArg->homeHtmlToPageHtmlRule.toPageHtmlRule.end = GetStrstrstr(pTmpBuff, 
                         "\"end\":\"", 
                         "\",")))
                 {
                   fprintf(stderr, "fail to Strstrstr %s\n", pDataArg->dirPath);
                   return false;
                 }
                 return true;
               }
        default:{ /* read config fail */
                  fprintf(stderr, "fail to read config:%s\n", pDataArg->dirPath);
                  return false;
                }
      }
    }
  }

  return true;
}
  
  template <typename D>
const char *Spider<D>::UrlToHtml(__IN const char *pUrlArg, 
    __IN const char *pSavePathArg, 
    __IN const char *pSaveFilenameArg)
{
	if (access(pSavePathArg, F_OK)) /* 如果文件夹不存创建 */
	{
    if (-1 == mkdir(pSavePathArg, 0777))
    {
      fprintf(stderr, "fail to mkdir of UrlToHtml:%s\n", pSavePathArg);
      return NULL;
    }
	}
  
  char pTmpBuff[__SPIDER_STR_LEN_2048__] = {0};
  FILE *fpDownloadHtml = NULL;
  char *pHttpStr = NULL;
	
	if ((strlen(pSavePathArg) + strlen(pSaveFilenameArg)) > sizeof(pTmpBuff))
	{
    fprintf(stderr, "fail to create file name of UrlToHtml\n");
    return NULL;
	}

  sprintf(pTmpBuff, "%s%s", pSavePathArg, pSaveFilenameArg);
	if (NULL == (fpDownloadHtml = fopen(pTmpBuff, "w")))
	{
    fprintf(stderr, "fail to fopen of UrlToHtml\n");
    return NULL;
	}

  FUNC_PRINTF_DEBUG("1================\n");
	pHttpStr = HttpsToStr(pUrlArg, __HTTPS_REQUES_HTML_SIZE__);
  FUNC_PRINTF_DEBUG("2================\n");
	if (0 > fprintf(fpDownloadHtml, "%s", pHttpStr))
	{
    fprintf(stderr, "fail to fprintf of HttpHomeHtmlToPageHtml");
    return NULL;
	}
  FUNC_PRINTF_DEBUG("3================\n");

	fclose(fpDownloadHtml);
	free(pHttpStr);
  
  return pUrlArg;
}

/* 先是输入链接，然后利用匹配器对链接进行匹配，
 * 如果是预设http链接，则进行http内部资源获取，下载html页面，
 * 并解析html页面里面有多少待处理（http box）资源，
 * */
/* 模板函数不能分开定义，在头文件中定义他吧。 */
  template <typename D>
void *Spider<D>::HttpUrlToHomeHtml(__IN const char *data, __INOUT Spider<const char *> *pThis)
{
  FUNC_PRINTF_DEBUG("HttpUrlToHomeHtml %s\n", data);
	char *pHttpStr = NULL;
 	FILE *fpDownloadBoxHtml = NULL;
	char pTmpBuff[__SPIDER_STR_LEN_2048__] = {0};
	const char *pTmpCh = NULL;
	char pTmpName[__SPIDER_STR_LEN_64__] = {0};
	int base = 0;
  int i = 0;
  FUNC_PRINTF_DEBUG("1 &&&&&&&&&&&&&\n");
	
	if (NULL == (pTmpCh = strstr(data, "//")))
	{
    FUNC_PRINTF_DEBUG("1.1 &&&&&&&&&&&&&\n");
    base = 0;
	}
	else
	{
    FUNC_PRINTF_DEBUG("1.2 &&&&&&&&&&&&&\n");
    base = pTmpCh + strlen("//") - data;
	}
  FUNC_PRINTF_DEBUG("2 &&&&&&&&&&&&&\n");
	if (NULL == (pTmpCh = strstr(data + base, "/")))
  {
    pTmpCh = data + strlen(data);
  }
	for (i = 0; i < (pTmpCh - (data + base)); ++i)
	{
    pTmpName[i] = data[base + i];
	}
	pTmpName[i] = '\0';
  FUNC_PRINTF_DEBUG("3 &&&&&&&&&&&&&\n");

	if ((strlen(__DOWNLOAD_PATH__) + strlen(pTmpName)) > sizeof(pTmpBuff))
	{
    fprintf(stderr, "fail to create dir name of HttpHomeHtmlToPageHtml\n");
    return NULL;
	}
	sprintf(pTmpBuff, "%s%s/", __DOWNLOAD_PATH__, pTmpName);

  if (NULL == UrlToHtml(data, pTmpBuff, "home.html"))
  {
    fprintf(stderr, "fial to UrlToHtml\n");
    return NULL;
  }

  FUNC_PRINTF_DEBUG("4================\n");
  /* 安排下一步任务 */
  ((Spider<D> *)pThis)->m_workList->push(pair<D, WORK_FUNCTION_T<D> >(((Spider<D> *)pThis)->m_data, HttpHomeHtmlToPageHtml));
  
	return (void *)data;	
}

  template <typename D>
void *Spider<D>::HttpUrlToHomeHtml(__IN SPIDER_DOWNLOAD_DATA_S *data, Spider<SPIDER_DOWNLOAD_DATA_S *> *pThis)
{
  FUNC_PRINTF_DEBUG("HttpUrlToHomeHtml D url:[%p]\n", &data->url);
  FUNC_PRINTF_DEBUG("HttpUrlToHomeHtml D url:%s\n", data->url);
  HttpUrlToHomeHtml(data->url, (Spider<const char *> *)pThis);

  return (void *)data;
}

  template <typename D>
void *Spider<D>::HttpHomeHtmlToPageHtml(__IN const char *data, __INOUT Spider<const char *> *pThis)
{ 
  FUNC_PRINTF_DEBUG("HttpHomeHtmlToPageHtml\n");
  return (void *)data;
}

  template <typename D>
void *Spider<D>::HttpHomeHtmlToPageHtml(__IN SPIDER_DOWNLOAD_DATA_S *data, __INOUT Spider<SPIDER_DOWNLOAD_DATA_S *> *pThis)
{ 
  FUNC_PRINTF_DEBUG("HttpHomeHtmlToPageHtml D\n");

  return (void *)data;
}

#endif//__SPIDER_H__
