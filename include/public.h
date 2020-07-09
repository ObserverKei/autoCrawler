#ifndef	__PUBLIC_H__
#define __PUBLIC_H__

#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include "kalg.h"

using namespace std;
using namespace kalg;
 
#define __IN  /* 输入 */
#define __OUT /* 输出 */
#define __INOUT /* 输入输出 */
#define __HTTPS_REQUES_HTML_SIZE__      (64 * 1024)
#define __DOWNLOAD_PATH__               ("./download/")
#define __SPIDER_STR_LEN_64__           (64)
#define __SPIDER_STR_LEN_1024__         (1024)
#define __SPIDER_STR_LEN_2048__         (2048)
#define __SPIDER_STR_LEN_4096__         (4096)
#define __SPIDER_DEBUG_FLAG__           (false)

#define FUNC_PRINTF_DEBUG(val...) do{ if(__SPIDER_DEBUG_FLAG__) { printf(val); } } while (0) 

#endif//__PUBLIC_H__

