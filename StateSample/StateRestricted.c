
#include <stdio.h>
#include <apr_strings.h>
#include "StateRestricted.h"
#include "Account.h"
#include "StateNormal.h"
#include "StateOverDraft.h"

//属性、方法声明
static void StateCheck(IState *pState);

struct StateRestricted_Fld
{
    apr_pool_t *m_pPool;

	IState m_state;

	Account *m_pAccount;
};

static void Free(IState **ppState)
{
	StateRestricted_Free(&(StateRestricted *)(*ppState)->pImplicit);
    *ppState = NULL;
}

static Account *GetAccount(IState *pState)
{
	StateRestricted *pInst = (StateRestricted *)pState->pImplicit;
    return pInst->pFld->m_pAccount;
}

static void SetAccount(IState *pState, Account *pAccount)
{
	StateRestricted *pInst = (StateRestricted *)pState->pImplicit;

    pInst->pFld->m_pAccount = pAccount;
}

static void Deposit(IState *pState, double dblAmount)
{
	StateRestricted *pInst = (StateRestricted *)pState->pImplicit;
    
    pInst->pFld->m_pAccount->SetBalance(pInst->pFld->m_pAccount, pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount) + dblAmount);
    StateCheck(pState);
}

static void Withdraw(IState *pState, double dblAmount)
{
    //StateRestricted *pInst = (StateRestricted *)pState->pImplicit;

    printf("账号受限，取款失败！\n");
}

static void CalcInterest(IState *pState)
{
    //StateRestricted *pInst = (StateRestricted *)pState->pImplicit;

    printf("计算利息！\n");
}

static void StateCheck(IState *pState)
{
	StateRestricted *pInst = (StateRestricted *)pState;

    double dblBalanceTmp = pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount);
    if (dblBalanceTmp > 0)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, StateNormal2IState(StateNormal_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
    else if (dblBalanceTmp > -2000)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, StateOverDraft2IState(StateOverDraft_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
}

static char *StateDesc(IState *pState, apr_pool_t *pPool)
{
    //StateRestricted *pInst = (StateRestricted *)pState->pImplicit;
    return apr_pstrdup(pPool, "Restricted");
}

StateRestricted * StateRestricted_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	StateRestricted *pInst = apr_palloc(pPool, sizeof(StateRestricted));

    pInst->pFld = apr_palloc(pPool, sizeof(StateRestricted_Fld));
    pInst->pFld->m_pPool;
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

IState * StateRestricted2IState(StateRestricted * pInst)
{
	return &(pInst->pFld->m_state);
}

void StateRestricted_Free(StateRestricted **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
