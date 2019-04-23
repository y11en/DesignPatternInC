
#include <apr_pools.h>
#include "IImage.h"


#ifndef IMAGEGIF_H
#define IMAGEGIF_H

typedef struct ImageGif_Fld ImageGif_Fld;
typedef struct ImageGif ImageGif;

struct ImageGif
{
    ImageGif_Fld *pFld;

    //实现接口，通过接口调用，
    //无需其他的公共方法
};

ImageGif *ImageGif_New(apr_pool_t *pSupPool);
IImage *ImageGif2IImage(ImageGif *pInst);
void ImageGif_Free(ImageGif **ppInst);

#endif // !IMAGEGIF_H
