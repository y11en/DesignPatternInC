
#include <stdio.h>
#include "DisplayHelp.h"

struct DisplayHelp_Fld
{
    apr_pool_t *m_pPool;
};

static void Display(DisplayHelp *pInst)
{
    puts("ÏÔÊ¾°ïÖúÎÄµµ¡£");
}

DisplayHelp * DisplayHelp_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DisplayHelp *pInst = apr_palloc(pPool, sizeof(DisplayHelp));

    pInst->pFld = apr_palloc(pPool, sizeof(DisplayHelp_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->Display = Display;

    return pInst;
}

void DisplayHelp_Free(DisplayHelp ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
