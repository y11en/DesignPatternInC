
#include <apr_pools.h>
#include "IFile.h"


#ifndef FOLDER_H
#define FOLDER_H

typedef struct Folder_Fld Folder_Fld;
typedef struct Folder Folder;

struct Folder
{
	Folder_Fld *pFld;
};

Folder *Folder_New(apr_pool_t *pSupPool, const char *const pName);
IFile *Folder2IFile(Folder *pInst);
void Folder_Free(Folder **ppInst);

#endif // !FOLDER_H
