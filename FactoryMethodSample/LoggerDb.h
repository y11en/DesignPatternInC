
#include <apr_pools.h>
#include "ILogger.h"

#ifndef LOGGERDB_H
#define LOGGERDB_H

typedef struct LoggerDb_Fld LoggerDb_Fld;
typedef struct LoggerDb LoggerDb;

struct LoggerDb
{
	LoggerDb_Fld *pFld;

	//公有方法声明
};

LoggerDb *LoggerDb_New(apr_pool_t *pSupPool);
ILogger *LoggerDb2ILogger(LoggerDb *pInst);
void LoggerDb_Free(LoggerDb **ppInst);

#endif // !LOGGERDB_H
