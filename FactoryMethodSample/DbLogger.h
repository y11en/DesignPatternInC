
#include <apr_pools.h>
#include "ILogger.h"

#ifndef DBLOGGER_H
#define DBLOGGER_H

typedef struct DbLogger_Fld DbLogger_Fld;
typedef struct DbLogger DbLogger;

struct DbLogger
{
	DbLogger_Fld *pFld;

	//公有方法声明
};

DbLogger *DbLogger_New(apr_pool_t *pSupPool);
ILogger *DbLogger2ILogger(DbLogger *pInst);
void DbLogger_Free(DbLogger **ppInst);

#endif // !DBLOGGER_H
