
#include <stdio.h>
#include <apr_strings.h>
#include "Account.h"
#include "IState.h"
#include "Normal.h"

struct Account_Fld
{
	apr_pool_t *m_pPool;

	IState *m_pState;

	char *m_pOwner;

	double m_dblBalance;
};

static double GetBalance(Account *pInst)
{
	return pInst->pFld->m_dblBalance;
}

static void SetBalance(Account *pInst, double dblBalance)
{
	pInst->pFld->m_dblBalance = dblBalance;
}

static void SetState(Account *pInst, IState *pState)
{
    pInst->pFld->m_pState->Free(&(pInst->pFld->m_pState));
    pInst->pFld->m_pState = pState;
    pInst->pFld->m_pState->SetAccount(pInst->pFld->m_pState, pInst);
}

static void Deposit(Account *pInst, double dblAmount)
{
	printf("%s存款%f。\n", pInst->pFld->m_pOwner, dblAmount);

	pInst->pFld->m_pState->Deposit(pInst->pFld->m_pState, dblAmount);

	printf("现在的余额为%f。\n", pInst->pFld->m_dblBalance);
	printf("现在的账户状态为%s\n", pInst->pFld->m_pState->StateDesc(pInst->pFld->m_pState, pInst->pFld->m_pPool));
	printf("-----------------------------------------\n");
}

static void Withdraw(Account *pInst, double dblAmount)
{
	printf("%s取款%f。\n", pInst->pFld->m_pOwner, dblAmount);

	pInst->pFld->m_pState->Withdraw(pInst->pFld->m_pState, dblAmount);

	printf("现在余额为%f。\n", pInst->pFld->m_dblBalance);
	printf("现在账户状态为%s\n", pInst->pFld->m_pState->StateDesc(pInst->pFld->m_pState, pInst->pFld->m_pPool));
	printf("-----------------------------------------\n");
}

static void CalcInterest(Account *pInst)
{
	pInst->pFld->m_pState->CalcInterest(pInst->pFld->m_pState);
}

Account * Account_New(apr_pool_t * pSupPool, double dblInitBalance, const char * pOwner)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Account *pInst = apr_palloc(pPool, sizeof(Account));

	pInst->pFld = apr_palloc(pPool, sizeof(Account_Fld));
	pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_pState = Normal2IState(Normal_New(pInst->pFld->m_pPool));//初始账户状态为正常状态
    pInst->pFld->m_pState->SetAccount(pInst->pFld->m_pState, pInst);//关联账户与账户状态
	pInst->pFld->m_pOwner = apr_pstrdup(pInst->pFld->m_pPool, pOwner);
	pInst->pFld->m_dblBalance = dblInitBalance;

	pInst->GetBalance = GetBalance;
	pInst->SetBalance = SetBalance;
	pInst->SetState = SetState;
	pInst->Deposit = Deposit;
	pInst->Withdraw = Withdraw;
	pInst->CalcInterest = CalcInterest;

	printf("%s开户，初始金额为%f。\n", pInst->pFld->m_pOwner, pInst->pFld->m_dblBalance);
	printf("---------------------------------------------\n");

	return pInst;
}

void Account_Free(Account **ppInst)
{
    (*ppInst)->pFld->m_pState->Free(&((*ppInst)->pFld->m_pState));

	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
