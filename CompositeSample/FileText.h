
#include <apr_pools.h>
#include "IFile.h"


#ifndef FILETEXT_H
#define FILETEXT_H

typedef struct FileText_Fld FileText_Fld;
typedef struct FileText FileText;

struct FileText
{
	FileText_Fld *pFld;
};

FileText *FileText_New(apr_pool_t *pSupPool, const char *const pName);
IFile *FileText2IFile(FileText *pInst);
void FileText_Free(FileText **ppInst);

#endif // !FILETEXT_H
