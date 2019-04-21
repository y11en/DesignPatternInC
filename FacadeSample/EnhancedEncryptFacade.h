
#include <apr_pools.h>
#include "IEncryptFacade.h"


#ifndef ENHANCEDENCRYPTFACADE_H
#define ENHANCEDENCRYPTFACADE_H

typedef struct EnhancedEncryptFacade_Fld EnhancedEncryptFacade_Fld;
typedef struct EnhancedEncryptFacade EnhancedEncryptFacade;

struct EnhancedEncryptFacade
{
    EnhancedEncryptFacade_Fld *pFld;

    //继承接口，面向接口编码，
    //因此，接口的公共方法不需要在此声明
};

EnhancedEncryptFacade *EnhancedEncryptFacade_New(apr_pool_t *pSupPool);
IEncryptFacade *EnhancedEncryptFacade2IEncryptFacade(EnhancedEncryptFacade *pInst);
void EnhancedEncryptFacade_Free(EnhancedEncryptFacade **ppInst);

#endif // !ENHANCEDENCRYPTFACADE_H
