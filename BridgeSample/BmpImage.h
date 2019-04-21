
#include <apr_pools.h>
#include "Image.h"


#ifndef BMPIMAGE_H
#define BMPIMAGE_H

typedef struct BmpImage_Fld BmpImage_Fld;
typedef struct BmpImage BmpImage;

struct BmpImage
{
	BmpImage_Fld *pFld;

	//实现接口，通过接口调用该类实例，
	//没有公有方法
};

BmpImage *BmpImage_New(apr_pool_t *pSupPool);
Image *BmpImage2Image(BmpImage *pInst);
void BmpImage_Free(BmpImage **ppInst);

#endif // !BMPIMAGE_H
