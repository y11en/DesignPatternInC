
#include "LoggerDb.h"


static void WriteLog();
static void Free(ILogger **ppLogger);

struct LoggerDb_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	ILogger m_logger;
};

static void WriteLog()
{
	puts("数据库日志记录!");
}

static void Free(ILogger **ppLogger)
{
	if (!ppLogger || !(*ppLogger))
	{
		return;
	}

	LoggerDb_Free(&(LoggerDb *)(*ppLogger)->pImplicit);
	*ppLogger = NULL;
}

LoggerDb * LoggerDb_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	LoggerDb *pInst = apr_palloc(pPool, sizeof(LoggerDb));

	pInst->pFld = apr_palloc(pPool, sizeof(LoggerDb_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_logger.pImplicit = pInst;
	pInst->pFld->m_logger.Free = Free;

	pInst->pFld->m_logger.WriteLog = WriteLog;

	//初始化私有成员

	//初始化公有方法

	return pInst;
}

ILogger * LoggerDb2ILogger(LoggerDb * pInst)
{
	return &(pInst->pFld->m_logger);
}

void LoggerDb_Free(LoggerDb ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
