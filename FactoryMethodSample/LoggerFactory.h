
#include <apr_pools.h>
#include "ILogger.h"

#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

typedef enum FactoryType FactoryType;

enum FactoryType
{
	FACTORY_NULL = 0,
	FACTORY_FILE_LOGGER = 1,
	FACTORY_DATABASE_LOGGER = 2
};

//工厂类型本质就一个创建对象的方法，
//在这里，因此只用一个函数指针来替代
typedef ILogger *(* LoggerFactory)(apr_pool_t *pSupPool);

//创建工厂
LoggerFactory CreateFactory(FactoryType type);

#endif // !LOGGERFACTORY_H
