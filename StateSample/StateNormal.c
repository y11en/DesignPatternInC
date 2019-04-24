
#include <stdio.h>
#include <apr_strings.h>
#include "StateNormal.h"
#include "Account.h"
#include "StateOverDraft.h"
#include "StateRestricted.h"

//属性、方法声明
static void StateCheck(IState *pState);

struct StateNormal_Fld
{
    apr_pool_t *m_pPool;

    IState m_state;

    Account *m_pAccount;
};

static void Free(IState **ppState)
{
	StateNormal_Free(&(StateNormal *)(*ppState)->pImplicit);
    *ppState = NULL;
}

static Account *GetAccount(IState *pState)
{
	StateNormal *pInst = (StateNormal *)pState->pImplicit;

    return pInst->pFld->m_pAccount;
}

static void SetAccount(IState *pState, Account *pAccount)
{
	StateNormal *pInst = (StateNormal *)pState->pImplicit;

    pInst->pFld->m_pAccount = pAccount;
}

static void Deposit(IState *pState, double dblAmount)
{
	StateNormal *pInst = (StateNormal *)pState->pImplicit;

    pInst->pFld->m_pAccount->SetBalance(pInst->pFld->m_pAccount, pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount) + dblAmount);
    StateCheck(pState);
}

static void Withdraw(IState *pState, double dblAmount)
{
	StateNormal *pInst = (StateNormal *)pState->pImplicit;

    pInst->pFld->m_pAccount->SetBalance(pInst->pFld->m_pAccount, pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount) - dblAmount);
    StateCheck(pState);
}

static void CalcInterest(IState *pState)
{
    //StateNormal *pInst = (StateNormal *)pState->pImplicit;
    printf("正常状态，无需支付利息！\n");
}

static char *StateDesc(IState *pState, apr_pool_t *pPool)
{
    //StateNormal *pInst = (StateNormal *)pState->pImplicit;
    return apr_pstrdup(pPool, "Normal");
}

static void StateCheck(IState *pState)
{
	StateNormal *pInst = (StateNormal *)pState->pImplicit;

    double dblBalanceTmp = pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount);
    if (dblBalanceTmp > -2000 && dblBalanceTmp <= 0)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, StateOverDraft2IState(StateOverDraft_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
    else if (dblBalanceTmp == -2000)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, StateRestricted2IState(StateRestricted_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
    else if (dblBalanceTmp < -2000)
    {
        printf("操作受限！\n");
    }
}

StateNormal * StateNormal_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	StateNormal *pInst = apr_palloc(pPool, sizeof(StateNormal));

    pInst->pFld = apr_palloc(pPool, sizeof(StateNormal_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_state.pImplicit = pInst;
    pInst->pFld->m_state.Free = Free;

    pInst->pFld->m_state.GetAccount = GetAccount;
    pInst->pFld->m_state.SetAccount = SetAccount;
    pInst->pFld->m_state.Deposit = Deposit;
    pInst->pFld->m_state.Withdraw = Withdraw;
    pInst->pFld->m_state.CalcInterest = CalcInterest;
    pInst->pFld->m_state.StateCheck = StateCheck;
    pInst->pFld->m_state.StateDesc = StateDesc;

    pInst->pFld->m_pAccount = NULL;

    return pInst;
}

IState * StateNormal2IState(StateNormal * pInst)
{
    return &(pInst->pFld->m_state);
}

void StateNormal_Free(StateNormal ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
