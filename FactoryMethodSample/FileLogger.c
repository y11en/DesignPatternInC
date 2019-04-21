
#include "FileLogger.h"


static void WriteLog();
static void Free(ILogger **ppLogger);

struct FileLogger_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	ILogger m_logger;
};

static void WriteLog()
{
	puts("文件日志记录!");
}

static void Free(ILogger **ppLogger)
{
	if (!ppLogger || !(*ppLogger))
	{
		return;
	}

	FileLogger_Free(&(FileLogger *)(*ppLogger)->pImplicit);
	*ppLogger = NULL;
}

FileLogger * FileLogger_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	FileLogger *pInst = (FileLogger *)apr_palloc(pPool, sizeof(FileLogger));

	pInst->pFld = (FileLogger_Fld *)apr_palloc(pPool, sizeof(FileLogger_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_logger.pImplicit = pInst;
	pInst->pFld->m_logger.Free = Free;

	pInst->pFld->m_logger.WriteLog = WriteLog;

	//私有成员初始化

	//公有方法初始化

	return pInst;
}

ILogger * FileLogger2ILogger(FileLogger * pInst)
{
	return &(pInst->pFld->m_logger);
}

void FileLogger_Free(FileLogger ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
