
#include <malloc.h>
#include <apr_strings.h>
#include "Memento.h"

struct Memento_Fld
{
    apr_pool_t *m_pPool;

    char *m_pLabel;
    int m_nX;
    int m_nY;
};

static char *GetLabel(Memento *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pLabel);
}

static void SetLabel(Memento *pInst, const char *pLabel)
{
	free(pInst->pFld->m_pLabel);
	pInst->pFld->m_pLabel = memcpy(malloc(strlen(pLabel) + 1), pLabel, strlen(pLabel) + 1);
}

static int GetX(Memento *pInst)
{
    return pInst->pFld->m_nX;
}

static void SetX(Memento *pInst, int nX)
{
    pInst->pFld->m_nX = nX;
}

static int GetY(Memento *pInst)
{
    return pInst->pFld->m_nY;
}

static void SetY(Memento *pInst, int nY)
{
    pInst->pFld->m_nY = nY;
}

Memento * Memento_New(apr_pool_t * pSupPool, const char * pLabel, int nX, int nY)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Memento *pInst = apr_palloc(pPool, sizeof(Memento));

    pInst->pFld = apr_palloc(pPool, sizeof(Memento_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_pLabel = memcpy(malloc(strlen(pLabel) + 1), pLabel, strlen(pLabel) + 1);
    pInst->pFld->m_nX = 0;
    pInst->pFld->m_nY = 0;

    pInst->GetLabel = GetLabel;
    pInst->SetLabel = SetLabel;
    pInst->GetX = GetX;
    pInst->SetX = SetX;
    pInst->GetY = GetY;
    pInst->SetY = SetY;

    return pInst;
}

void Memento_Free(Memento ** ppInst)
{
	free((*ppInst)->pFld->m_pLabel);
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
