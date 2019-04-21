
#include <apr_pools.h>


#ifndef LOGGER_H
#define LOGGER_H

typedef struct Logger_Fld Logger_Fld;
typedef struct Logger Logger;

struct Logger
{
	Logger_Fld *pFld;

	void (* Log)(Logger *pInst, const char *pUserID);
};

Logger *Logger_New(apr_pool_t *pSupPool);
void Logger_Free(Logger **ppInst);

#endif // !LOGGER_H
