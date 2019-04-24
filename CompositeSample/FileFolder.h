
#include <apr_pools.h>
#include "IFile.h"


#ifndef FILEFOLDER_H
#define FILEFOLDER_H

typedef struct FileFolder_Fld FileFolder_Fld;
typedef struct FileFolder FileFolder;

struct FileFolder
{
	FileFolder_Fld *pFld;
};

FileFolder *FileFolder_New(apr_pool_t *pSupPool, const char *const pName);
IFile *FileFolder2IFile(FileFolder *pInst);
void FileFolder_Free(FileFolder **ppInst);

#endif // !FILEFOLDER_H
