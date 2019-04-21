
#include <apr_pools.h>
#include "IState.h"


#ifndef OVERDRAFT_H
#define OVERDRAFT_H

typedef struct OverDraft_Fld OverDraft_Fld;
typedef struct OverDraft OverDraft;

struct OverDraft
{
    OverDraft_Fld *pFld;
};

OverDraft *OverDraft_New(apr_pool_t *pSupPool);
IState *OverDraft2IState(OverDraft *pInst);
void OverDraft_Free(OverDraft **ppInst);

#endif // !OVERDRAFT_H
