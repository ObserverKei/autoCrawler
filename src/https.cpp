#include "public.h"
#include "https.h"

char *ReturnStr = NULL;

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{

	/*	ReturnStr = malloc(size * nmemb);
	**	这个不可行,因为 libcurl 会调用多次这个函数,防止接收到的数据过大,
	**	libcurl他设置的缓存有限额,超过限额就会分段传送;
 	*/

	/* 进行数据的保存,注意一下,这个ReturnStr能存入的数据必须足够大才可以 */	
	strncat(ReturnStr, (char *)buffer, size * nmemb);

	return  size * nmemb;
}

char *HttpsToStr(const char *urlArg, int real_size)
{
	/*	申请存放网页返回源码的堆区空间	*/
	ReturnStr = (char *)malloc(real_size);

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	if(curl) 
	{
		/* urlArg EG: "https://www.baidu.com/" */
		curl_easy_setopt(curl, CURLOPT_URL, urlArg);
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_data);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if(res != CURLE_OK)
		{
			/* Error source */
			fprintf(stderr, "curl_easy_perform() failed: %s\n",	curl_easy_strerror(res));
			return NULL;
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return ReturnStr;
}
