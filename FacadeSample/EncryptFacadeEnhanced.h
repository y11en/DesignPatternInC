
#include <apr_pools.h>
#include "IEncryptFacade.h"


#ifndef ENCRYPTFACADEENHANCED_H
#define ENCRYPTFACADEENHANCED_H

typedef struct EncryptFacadeEnhanced_Fld EncryptFacadeEnhanced_Fld;
typedef struct EncryptFacadeEnhanced EncryptFacadeEnhanced;

struct EncryptFacadeEnhanced
{
	EncryptFacadeEnhanced_Fld *pFld;

    //继承接口，面向接口编码，
    //因此，接口的公共方法不需要在此声明
};

EncryptFacadeEnhanced *EncryptFacadeEnhanced_New(apr_pool_t *pSupPool);
IEncryptFacade *EncryptFacadeEnhanced2IEncryptFacade(EncryptFacadeEnhanced *pInst);
void EncryptFacadeEnhanced_Free(EncryptFacadeEnhanced **ppInst);

#endif // !ENCRYPTFACADEENHANCED_H
