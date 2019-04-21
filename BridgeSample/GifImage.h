
#include <apr_pools.h>
#include "Image.h"


#ifndef GIFIMAGE_H
#define GIFIMAGE_H

typedef struct GifImage_Fld GifImage_Fld;
typedef struct GifImage GifImage;

struct GifImage
{
    GifImage_Fld *pFld;

    //实现接口，通过接口调用，
    //无需其他的公共方法
};

GifImage *GifImage_New(apr_pool_t *pSupPool);
Image *GifImage2Image(GifImage *pInst);
void GifImage_Free(GifImage **ppInst);

#endif // !GIFIMAGE_H
