
#include <apr_pools.h>
#include "IImageImp.h"


#ifndef IMAGEIMPUNIX_H
#define IMAGEIMPUNIX_H

typedef struct ImageImpUnix_Fld ImageImpUnix_Fld;
typedef struct ImageImpUnix ImageImpUnix;

struct ImageImpUnix
{
    ImageImpUnix_Fld *pFld;

	//实现接口，通过接口调用，因此没有公共方法
};

ImageImpUnix *ImageImpUnix_New(apr_pool_t *pSubPool);
IImageImp *ImageImpUnix2IImageImp(ImageImpUnix *pInst);
void ImageImpUnix_Free(ImageImpUnix **ppInst);

#endif // !IMAGEIMPUNIX_H
