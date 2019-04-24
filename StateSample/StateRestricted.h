
#include <apr_pools.h>
#include "IState.h"


#ifndef STATERESTRICTED_H
#define STATERESTRICTED_H

typedef struct StateRestricted_Fld StateRestricted_Fld;
typedef struct StateRestricted StateRestricted;

struct StateRestricted
{
	StateRestricted_Fld *pFld;
};

StateRestricted *StateRestricted_New(apr_pool_t *pSupPool);
IState *StateRestricted2IState(StateRestricted *pInst);
void StateRestricted_Free(StateRestricted **ppInst);

#endif // !STATERESTRICTED_H
