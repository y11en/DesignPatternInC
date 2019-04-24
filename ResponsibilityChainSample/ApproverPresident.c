
#include <stdio.h>
#include <apr_strings.h>
#include "ApproverPresident.h"

struct ApproverPresident_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IApprover m_approver;

    //后继责任处理者
    IApprover *m_pSuccessor;

    //处理者姓名
    char *m_pName;
};

static void Free(IApprover **ppApprover)
{
	ApproverPresident_Free(&(ApproverPresident *)(*ppApprover)->pImplicit);
    *ppApprover = NULL;
}

static void SetSuccessor(IApprover *pApprover, IApprover *pSuccessor)
{
	ApproverPresident *pInst = (ApproverPresident *)pApprover->pImplicit;
    pInst->pFld->m_pSuccessor = pSuccessor;
}

static void ProcessRequest(IApprover *pApprover, PurchaseRequest *pRequest)
{
	ApproverPresident *pInst = (ApproverPresident *)pApprover->pImplicit;

    if (pRequest->GetAmount(pRequest) < 500000)
    {
        printf("董事长%s审批采购单：%d，金额：%f元，采购目的：%s。\n", pInst->pFld->m_pName, pRequest->GetPurchaseCode(pRequest), pRequest->GetAmount(pRequest), pRequest->GetPurpose(pRequest, pInst->pFld->m_pPool));
    }
    else
    {
        pInst->pFld->m_pSuccessor->ProcessRequest(pInst->pFld->m_pSuccessor, pRequest);
    }
}

ApproverPresident * ApproverPresident_New(apr_pool_t * pSupPool, const char * pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	ApproverPresident *pInst = apr_palloc(pPool, sizeof(ApproverPresident));

    pInst->pFld = apr_palloc(pPool, sizeof(ApproverPresident_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_approver.pImplicit = pInst;
    pInst->pFld->m_approver.Free = Free;

    pInst->pFld->m_approver.SetSuccessor = SetSuccessor;
    pInst->pFld->m_approver.ProcessRequest = ProcessRequest;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_pSuccessor = NULL;

    return pInst;
}

IApprover * ApproverPresident2IApprover(ApproverPresident * pInst)
{
    return &(pInst->pFld->m_approver);
}

void ApproverPresident_Free(ApproverPresident ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
