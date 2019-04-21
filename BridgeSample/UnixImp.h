
#include <apr_pools.h>
#include "ImageImp.h"


#ifndef UNIXIMP_H
#define UNIXIMP_H

typedef struct UnixImp_Fld UnixImp_Fld;
typedef struct UnixImp UnixImp;

struct UnixImp
{
	UnixImp_Fld *pFld;

	//实现接口，通过接口调用，因此没有公共方法
};

UnixImp *UnixImp_New(apr_pool_t *pSubPool);
ImageImp *UnixImp2ImageImp(UnixImp *pInst);
void UnixImp_Free(UnixImp **ppInst);

#endif // !UNIXIMP_H
