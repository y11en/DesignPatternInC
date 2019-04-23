
#include <apr_pools.h>
#include "IImageImp.h"


#ifndef IMAGEIMPLINUX_H
#define IMAGEIMPLINUX_H

typedef struct ImageImpLinux_Fld ImageImpLinux_Fld;
typedef struct ImageImpLinux ImageImpLinux;

struct ImageImpLinux
{
    ImageImpLinux_Fld *pFld;

	//继承接口，通过接口调用，
	//因此不设置公共方法
};

ImageImpLinux *ImageImpLinux_New(apr_pool_t *pSupPool);
//继承接口，须提供转换至接口的方法
IImageImp *ImageImpLinux2IImageImp(ImageImpLinux *pInst);
void ImageImpLinux_Free(ImageImpLinux **ppInst);

#endif // !IMAGEIMPLINUX_H
