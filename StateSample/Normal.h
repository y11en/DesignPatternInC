
#include <apr_pools.h>
#include "IState.h"


#ifndef NORMAL_H
#define NORMAL_H

typedef struct Normal_Fld Normal_Fld;
typedef struct Normal Normal;

struct Normal
{
	Normal_Fld *pFld;
};

Normal *Normal_New(apr_pool_t *pSupPool);
IState *Normal2IState(Normal *pInst);
void Normal_Free(Normal **ppInst);

#endif // !NORMAL_H
