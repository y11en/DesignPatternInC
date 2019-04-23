
#include <apr_pools.h>
#include "IImageImp.h"


#ifndef IMAGEIMPWINDOWS_H
#define IMAGEIMPWINDOWS_H

typedef struct ImageImpWindows_Fld ImageImpWindows_Fld;
typedef struct ImageImpWindows ImageImpWindows;

struct ImageImpWindows
{
    ImageImpWindows_Fld *pFld;

	//实现接口，通过接口调用，
	//不提供公有方法
};

ImageImpWindows *ImageImpWindows_New(apr_pool_t *pSupPool);
IImageImp *ImageImpWindows2IImageImp(ImageImpWindows *pInst);
void ImageImpWindows_Free(ImageImpWindows **ppInst);

#endif // !IMAGEIMPWINDOWS_H

