
#include <apr_pools.h>
#include "IState.h"


#ifndef RESTRICTED_H
#define RESTRICTED_H

typedef struct Restricted_Fld Restricted_Fld;
typedef struct Restricted Restricted;

struct Restricted
{
	Restricted_Fld *pFld;
};

Restricted *Restricted_New(apr_pool_t *pSupPool);
IState *Restricted2IState(Restricted *pInst);
void Restricted_Free(Restricted **ppInst);

#endif // !RESTRICTED_H
