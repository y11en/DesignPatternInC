
#include <stdio.h>
#include <apr_strings.h>
#include "ApproverManager.h"

struct ApproverManager_Fld
{
    apr_pool_t *m_pPool;

    IApprover m_approver;

    IApprover *m_pSuccessor;

    char *m_pName;
};

static void Free(IApprover **ppApprover)
{
	ApproverManager_Free(&(ApproverManager *)(*ppApprover)->pImplicit);
    *ppApprover = NULL;
}

static void SetSuccessor(IApprover *pApprover, IApprover *pSuccessor)
{
	ApproverManager *pInst = (ApproverManager *)pApprover->pImplicit;
    pInst->pFld->m_pSuccessor = pSuccessor;
}

static void ProcessRequest(IApprover *pApprover, PurchaseRequest *pRequest)
{
	ApproverManager *pInst = (ApproverManager *)pApprover->pImplicit;
    if (pRequest->GetAmount(pRequest) < 80000)
    {
        printf("经理%s审批采购单：%d，金额：%f元，采购目的：%s。\n", pInst->pFld->m_pName, pRequest->GetPurchaseCode(pRequest), pRequest->GetAmount(pRequest), pRequest->GetPurpose(pRequest, pInst->pFld->m_pPool));
    }
    else
    {
        pInst->pFld->m_pSuccessor->ProcessRequest(pInst->pFld->m_pSuccessor, pRequest);
    }
}

ApproverManager * ApproverManager_New(apr_pool_t * pSupPool, const char * pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	ApproverManager *pInst = apr_palloc(pPool, sizeof(ApproverManager));

    pInst->pFld = apr_palloc(pPool, sizeof(ApproverManager_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_approver.pImplicit = pInst;
    pInst->pFld->m_approver.Free = Free;

    pInst->pFld->m_approver.SetSuccessor = SetSuccessor;
    pInst->pFld->m_approver.ProcessRequest = ProcessRequest;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_pSuccessor = NULL;

    return pInst;
}

IApprover * ApproverManager2IApprover(ApproverManager * pInst)
{
    return &(pInst->pFld->m_approver);
}

void ApproverManager_Free(ApproverManager ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
