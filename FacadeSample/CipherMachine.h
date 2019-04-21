
#include <apr_pools.h>


#ifndef CIPHERMACHINE_H
#define CIPHERMACHINE_H

typedef struct CipherMachine_Fld CipherMachine_Fld;
typedef struct CipherMachine CipherMachine;

struct CipherMachine
{
    CipherMachine_Fld *pFld;

    char *(* Encrypt)(CipherMachine *pInst, const char *pPlainText, apr_pool_t *pPool);
};

CipherMachine *CipherMachine_New(apr_pool_t *pSupPool);
void CipherMachine_Free(CipherMachine **ppInst);

#endif // !CIPHERMACHINE_H
