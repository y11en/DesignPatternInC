
#include <stdio.h>
#include "SystemExit.h"

struct SystemExit_Fld
{
    apr_pool_t *m_pPool;
};

static void Exit(SystemExit *pInst)
{
    printf("ÍË³öÏµÍ³¡£\n");
}

SystemExit * SystemExit_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    SystemExit *pInst = apr_palloc(pPool, sizeof(SystemExit));

    pInst->pFld = apr_palloc(pPool, sizeof(SystemExit_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->Exit = Exit;

    return pInst;
}

void SystemExit_Free(SystemExit ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
