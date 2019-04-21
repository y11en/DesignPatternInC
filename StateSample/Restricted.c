
#include <stdio.h>
#include <apr_strings.h>
#include "Restricted.h"
#include "Account.h"
#include "Normal.h"
#include "OverDraft.h"

//属性、方法声明
static void StateCheck(IState *pState);

struct Restricted_Fld
{
    apr_pool_t *m_pPool;

	IState m_state;

	Account *m_pAccount;
};

static void Free(IState **ppState)
{
    Restricted_Free(&(Restricted *)(*ppState)->pImplicit);
    *ppState = NULL;
}

static Account *GetAccount(IState *pState)
{
    Restricted *pInst = (Restricted *)pState->pImplicit;
    return pInst->pFld->m_pAccount;
}

static void SetAccount(IState *pState, Account *pAccount)
{
    Restricted *pInst = (Restricted *)pState->pImplicit;

    pInst->pFld->m_pAccount = pAccount;
}

static void Deposit(IState *pState, double dblAmount)
{
    Restricted *pInst = (Restricted *)pState->pImplicit;
    
    pInst->pFld->m_pAccount->SetBalance(pInst->pFld->m_pAccount, pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount) + dblAmount);
    StateCheck(pState);
}

static void Withdraw(IState *pState, double dblAmount)
{
    //Restricted *pInst = (Restricted *)pState->pImplicit;

    printf("账号受限，取款失败！\n");
}

static void CalcInterest(IState *pState)
{
    //Restricted *pInst = (Restricted *)pState->pImplicit;

    printf("计算利息！\n");
}

static void StateCheck(IState *pState)
{
    Restricted *pInst = (Restricted *)pState;

    double dblBalanceTmp = pInst->pFld->m_pAccount->GetBalance(pInst->pFld->m_pAccount);
    if (dblBalanceTmp > 0)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, Normal2IState(Normal_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
    else if (dblBalanceTmp > -2000)
    {
        pInst->pFld->m_pAccount->SetState(pInst->pFld->m_pAccount, OverDraft2IState(OverDraft_New(apr_pool_parent_get(pInst->pFld->m_pPool))));
    }
}

static char *StateDesc(IState *pState, apr_pool_t *pPool)
{
    //Restricted *pInst = (Restricted *)pState->pImplicit;
    return apr_pstrdup(pPool, "Restricted");
}

Restricted * Restricted_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Restricted *pInst = apr_palloc(pPool, sizeof(Restricted));

    pInst->pFld = apr_palloc(pPool, sizeof(Restricted_Fld));
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

IState * Restricted2IState(Restricted * pInst)
{
	return &(pInst->pFld->m_state);
}

void Restricted_Free(Restricted **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
