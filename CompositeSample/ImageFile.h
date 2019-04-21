
#include <apr_pools.h>
#include "IFile.h"


#ifndef IMAGE_FILE_H
#define IMAGE_FILE_H

typedef struct ImageFile_Fld ImageFile_Fld;
typedef struct ImageFile ImageFile;

struct ImageFile
{
    ImageFile_Fld *pFld;
};

ImageFile *ImageFile_New(apr_pool_t *pSupPool, const char *const pName);
IFile *ImageFile2IFile(ImageFile *pInst);
void ImageFile_Free(ImageFile **ppInst);

#endif // !IMAGE_FILE_H
