
#include <stdio.h>
#include <apr_strings.h>
#include "Board.h"

struct Board_Fld
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
    Board_Free(&(Board *)(*ppApprover)->pImplicit);
    *ppApprover = NULL;
}

static void SetSuccessor(IApprover *pApprover, IApprover *pSuccessor)
{
    Board *pInst = (Board *)pApprover->pImplicit;
    pInst->pFld->m_pSuccessor = pSuccessor;
}

static void ProcessRequest(IApprover *pApprover, PurchaseRequest *pRequest)
{
    Board *pInst = (Board *)pApprover->pImplicit;
    printf("召开董事会审批采购订单: %d，金额: %f，采购目的: %s。\n", pRequest->GetPurchaseCode(pRequest), pRequest->GetAmount(pRequest), pRequest->GetPurpose(pRequest, pInst->pFld->m_pPool));
}

Board * Board_New(apr_pool_t *pSupPool, const char * pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Board *pInst = apr_palloc(pPool, sizeof(Board));

    pInst->pFld = apr_palloc(pPool, sizeof(Board_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_approver.pImplicit = pInst;
    pInst->pFld->m_approver.Free = Free;

    pInst->pFld->m_approver.SetSuccessor = SetSuccessor;
    pInst->pFld->m_approver.ProcessRequest = ProcessRequest;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_pSuccessor = NULL;

    return pInst;
}

IApprover *Board2IApprover(Board * pInst)
{
    return &(pInst->pFld->m_approver);
}

void Board_Free(Board ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
