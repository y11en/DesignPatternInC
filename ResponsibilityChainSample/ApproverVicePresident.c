
#include <stdio.h>
#include <apr_strings.h>
#include "ApproverVicePresident.h"

struct ApproverVicePresident_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IApprover m_approver;

    //后继责任处理者
    IApprover *m_pSuccessor;

    char *m_pName;
};

static void Free(IApprover **ppApprover)
{
	ApproverVicePresident_Free(&(ApproverVicePresident *)(*ppApprover)->pImplicit);
    *ppApprover = NULL;
}

static void SetSuccessor(IApprover *pApprover, IApprover *pSuccessor)
{
	ApproverVicePresident *pInst = (ApproverVicePresident *)pApprover->pImplicit;
    pInst->pFld->m_pSuccessor = pSuccessor;
}

static void ProcessRequest(IApprover *pApprover, PurchaseRequest *pRequest)
{
	ApproverVicePresident *pInst = (ApproverVicePresident *)pApprover->pImplicit;
    if (pRequest->GetAmount(pRequest) < 100000)
    {
        printf("副董事长%s审批采购单：%d，金额：%f元，采购目的：%s。\n", pInst->pFld->m_pName, pRequest->GetPurchaseCode(pRequest), pRequest->GetAmount(pRequest), pRequest->GetPurpose(pRequest, pInst->pFld->m_pPool));
    }
    else
    {
        pInst->pFld->m_pSuccessor->ProcessRequest(pInst->pFld->m_pSuccessor, pRequest);
    }
}

ApproverVicePresident * ApproverVicePresident_New(apr_pool_t * pSupPool, const char * pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	ApproverVicePresident *pInst = apr_palloc(pPool, sizeof(ApproverVicePresident));

    pInst->pFld = apr_palloc(pPool, sizeof(ApproverVicePresident_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_approver.pImplicit = pInst;
    pInst->pFld->m_approver.Free = Free;

    pInst->pFld->m_approver.SetSuccessor = SetSuccessor;
    pInst->pFld->m_approver.ProcessRequest = ProcessRequest;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_pSuccessor = NULL;

    return pInst;
}

IApprover * ApproverVicePresident2IApprover(ApproverVicePresident * pInst)
{
    return &(pInst->pFld->m_approver);
}

void ApproverVicePresident_Free(ApproverVicePresident ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
