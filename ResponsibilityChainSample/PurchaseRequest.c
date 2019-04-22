
#include <apr_strings.h>
#include "PurchaseRequest.h"

struct PurchaseRequest_Fld
{
    apr_pool_t *m_pPool;

    //²É¹º½ð¶î
    double m_dblAmount;
    //²É¹º±àÂë
    int m_nPurchaseCode;
    //ÓÃÍ¾ÃèÊö
    char *m_pPurpose;
};

static double GetAmount(PurchaseRequest *pInst)
{
    return pInst->pFld->m_dblAmount;
}

static void SetAmount(PurchaseRequest *pInst, double dblAmount)
{
    pInst->pFld->m_dblAmount = dblAmount;
}

static int GetPurchaseCode(PurchaseRequest *pInst)
{
    return pInst->pFld->m_nPurchaseCode;
}

static void SetPurchaseCode(PurchaseRequest *pInst, int nPurchaseCode)
{
    pInst->pFld->m_nPurchaseCode = nPurchaseCode;
}

static char *GetPurpose(PurchaseRequest *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pPurpose);
}

static void SetPurpose(PurchaseRequest *pInst, const char *pPurpose)
{
    pInst->pFld->m_pPurpose = apr_pstrdup(pInst->pFld->m_pPool, pPurpose);
}

PurchaseRequest * PurchaseRequest_New(apr_pool_t * pSupPool, double dblAmount, int nPurchaseCode, const char *pPurpose)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    PurchaseRequest *pInst = apr_palloc(pPool, sizeof(PurchaseRequest));

    pInst->pFld = apr_palloc(pPool, sizeof(PurchaseRequest_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_dblAmount = dblAmount;
    pInst->pFld->m_nPurchaseCode = nPurchaseCode;
    pInst->pFld->m_pPurpose = apr_pstrdup(pInst->pFld->m_pPool, pPurpose);

    pInst->GetAmount = GetAmount;
    pInst->SetAmount = SetAmount;
    pInst->GetPurchaseCode = GetPurchaseCode;
    pInst->SetPurchaseCode = SetPurchaseCode;
    pInst->GetPurpose = GetPurpose;
    pInst->SetPurpose = SetPurpose;

    return pInst;
}

void PurchaseRequest_Free(PurchaseRequest ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
