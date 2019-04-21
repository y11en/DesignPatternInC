
#include <apr_pools.h>
/*#include*/typedef struct IState IState;


#ifndef ACCOUNT_H
#define ACCOUTN_H

typedef struct Account_Fld Account_Fld;
typedef struct Account Account;

struct Account
{
	Account_Fld *pFld;

	double (* GetBalance)(Account *pInst);
	void (* SetBalance)(Account *pInst, double dblBalance);

	void (* SetState)(Account *pInst, IState *pState);//状态模式专用的设置状态的方法

	void (* Deposit)(Account *pInst, double dblAmount);
	void (* Withdraw)(Account *pInst, double dblAmount);
	void (* CalcInterest)(Account *ppInst);
};

Account *Account_New(apr_pool_t *pSupPool, double dblInitBalance, const char *pOwner);
void Account_Free(Account **ppInst);

#endif // !ACCOUNT_H
