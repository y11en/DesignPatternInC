
#include <apr_pools.h>
#include "ImageImp.h"


#ifndef LINUXIMP_H
#define LINUXIMP_H

typedef struct LinuxImp_Fld LinuxImp_Fld;
typedef struct LinuxImp LinuxImp;

struct LinuxImp
{
	LinuxImp_Fld *pFld;

	//继承接口，通过接口调用，
	//因此不设置公共方法
};

LinuxImp *LinuxImp_New(apr_pool_t *pSupPool);
//继承接口，须提供转换至接口的方法
ImageImp *LinuxImp2ImageImp(LinuxImp *pInst);
void LinuxImp_Free(LinuxImp **ppInst);

#endif // !LINUXIMP_H
