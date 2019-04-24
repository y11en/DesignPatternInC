
#include <apr_pools.h>
#include "ILogger.h"


#ifndef LOGGERFILE_H
#define LOGGERFILE_H

typedef struct LoggerFile_Fld LoggerFile_Fld;
typedef struct LoggerFile LoggerFile;

struct LoggerFile
{
	LoggerFile_Fld *pFld;

	//LoggerFile类公有方法声明
};

LoggerFile *LoggerFile_New(apr_pool_t *pSupPool);
ILogger *LoggerFile2ILogger(LoggerFile *pInst);
void LoggerFile_Free(LoggerFile **ppInst);

#endif // !LOGGERFILE_H
