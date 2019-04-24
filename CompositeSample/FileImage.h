
#include <apr_pools.h>
#include "IFile.h"


#ifndef FILEIMAGE_H
#define FILEIMAGE_H

typedef struct FileImage_Fld FileImage_Fld;
typedef struct FileImage FileImage;

struct FileImage
{
	FileImage_Fld *pFld;
};

FileImage *FileImage_New(apr_pool_t *pSupPool, const char *const pName);
IFile *FileImage2IFile(FileImage *pInst);
void FileImage_Free(FileImage **ppInst);

#endif // !FILEIMAGE_H
