
#include <stdio.h>
#include <apr_strings.h>
#include "Director.h"

struct Director_Fld
{
    apr_pool_t *m_pPool;

    IApprover m_approver;

    IApprover *m_pSuccessor;

    char *m_pName;
};

static void Free(IApprover **ppApprover)
{
    Director_Free(&(Director *)(*ppApprover)->pImplicit);
    *ppApprover = NULL;
}

static void SetSuccessor(IApprover *pApprover, IApprover *pSuccessor)
{
    Director *pInst = (Director *)pApprover->pImplicit;
    pInst->pFld->m_pSuccessor = pSuccessor;
}

static void ProcessRequest(IApprover *pApprover, PurchaseRequest *pRequest)
{
    Director *pInst = (Director *)pApprover->pImplicit;
    if (pRequest->GetAmount(pRequest) < 50000)
    {
        printf("主任%s审批采购单：%d，金额：%f元，采购目的：%s。\n", pInst->pFld->m_pName, pRequest->GetPurchaseCode(pRequest), pRequest->GetAmount(pRequest), pRequest->GetPurpose(pRequest, pInst->pFld->m_pPool));
    }
    else
    {
        pInst->pFld->m_pSuccessor->ProcessRequest(pInst->pFld->m_pSuccessor, pRequest);
    }
}

Director * Director_New(apr_pool_t * pSupPool, const char * pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Director *pInst = apr_palloc(pPool, sizeof(Director));

    pInst->pFld = apr_palloc(pPool, sizeof(Director_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_approver.pImplicit = pInst;
    pInst->pFld->m_approver.Free = Free;

    pInst->pFld->m_approver.SetSuccessor = SetSuccessor;
    pInst->pFld->m_approver.ProcessRequest = ProcessRequest;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_pSuccessor = NULL;

    return pInst;
}

IApprover * Director2IApprover(Director * pInst)
{
    return &(pInst->pFld->m_approver);
}

void Director_Free(Director ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
