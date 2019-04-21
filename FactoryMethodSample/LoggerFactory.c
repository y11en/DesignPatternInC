
#include "LoggerFactory.h"
#include "FileLogger.h"
#include "DbLogger.h"


static ILogger *FileLoggerFactory(apr_pool_t *pSupPool);
static ILogger *DbLoggerFactory(apr_pool_t *pSupPool);

LoggerFactory CreateFactory(FactoryType type)
{
	switch (type)
	{
	case FACTORY_NULL:
		return NULL;
	case FACTORY_FILE_LOGGER:
		return FileLoggerFactory;
	case FACTORY_DATABASE_LOGGER:
		return DbLoggerFactory;
	default:
		return NULL;
	}
}

//文件日志工厂
static ILogger *FileLoggerFactory(apr_pool_t *pSupPool)
{
	return FileLogger2ILogger(FileLogger_New(pSupPool));
}

//数据库日志工厂
static ILogger *DbLoggerFactory(apr_pool_t *pSupPool)
{
	return DbLogger2ILogger(DbLogger_New(pSupPool));
}
