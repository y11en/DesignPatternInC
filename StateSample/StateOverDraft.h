
#include <apr_pools.h>
#include "IState.h"


#ifndef STATEOVERDRAFT_H
#define STATEOVERDRAFT_H

typedef struct StateOverDraft_Fld StateOverDraft_Fld;
typedef struct StateOverDraft StateOverDraft;

struct StateOverDraft
{
	StateOverDraft_Fld *pFld;
};

StateOverDraft *StateOverDraft_New(apr_pool_t *pSupPool);
IState *StateOverDraft2IState(StateOverDraft *pInst);
void StateOverDraft_Free(StateOverDraft **ppInst);

#endif // !STATEOVERDRAFT_H
