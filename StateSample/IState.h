
#include <apr_pools.h>
/*#include*/typedef struct Account Account;


#ifndef ISTATE_H
#define ISTATE_H

typedef struct IState IState;

struct IState
{
	void *pImplicit;

	Account *(* GetAccount)(IState *pState);
	void (* SetAccount)(IState *pState, Account *pAccount);

	void (* Deposit)(IState *pState, double dblAmount);
	void (* Withdraw)(IState *pState, double dblAmount);
	void (* CalcInterest)(IState *pState);

	void (* StateCheck)(IState *pState);
	
    char *(* StateDesc)(IState *pState, apr_pool_t *pPool);

	void (* Free)(IState **ppState);
};

#endif // !ISTATE_H
