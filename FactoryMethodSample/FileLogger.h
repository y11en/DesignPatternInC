
#include <apr_pools.h>
#include "ILogger.h"


#ifndef FILELOGGER_H
#define FILELOGGER_H

typedef struct FileLogger_Fld FileLogger_Fld;
typedef struct FileLogger FileLogger;

struct FileLogger
{
	FileLogger_Fld *pFld;

	//FileLogger类公有方法声明
};

FileLogger *FileLogger_New(apr_pool_t *pSupPool);
ILogger *FileLogger2ILogger(FileLogger *pInst);
void FileLogger_Free(FileLogger **ppInst);

#endif // !FILELOGGER_H
