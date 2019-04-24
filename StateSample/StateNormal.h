
#include <apr_pools.h>
#include "IState.h"


#ifndef STATENORMAL_H
#define STATENORMAL_H

typedef struct StateNormal_Fld StateNormal_Fld;
typedef struct StateNormal StateNormal;

struct StateNormal
{
	StateNormal_Fld *pFld;
};

StateNormal *StateNormal_New(apr_pool_t *pSupPool);
IState *StateNormal2IState(StateNormal *pInst);
void StateNormal_Free(StateNormal **ppInst);

#endif // !STATENORMAL_H
