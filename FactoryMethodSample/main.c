
#include <stdio.h>
#include <apr_pools.h>
#include "ILogger.h"
#include "LoggerFactory.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;

	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

	LoggerFactory factory = CreateFactory(FACTORY_LOGGER_FILE);//创建生产指定产品的工厂
	ILogger *logger = factory(pMemPool);//生产产品
	//ILogger *logger = CreateFactory(FACTORY_FILE_LOGGER)(pMemPool);
	logger->WriteLog(logger);//使用产品
	logger->Free(&logger);

	if (!logger)
	{
		puts("\nNow logger is cleared..");
	}

	for (size_t i = 0; i < 5; i++)
	{
		factory = CreateFactory(FACTORY_LOGGER_DATABASE);
		logger = factory(pMemPool);
		logger->WriteLog(logger);
		logger->Free(&logger);
	}

	if (!logger)
	{
		puts("\nNow logger is cleared..");
	}

	apr_pool_destroy(pMemPool);

	apr_terminate();

	return EXIT_SUCCESS;
}