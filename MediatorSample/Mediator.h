
#include <apr_pools.h>
#include "ICardPlayer.h"


#ifndef MEDIATOR_H
#define MEDIATOR_H

typedef struct Mediator_Fld Mediator_Fld;
typedef struct Mediator Mediator;

struct Mediator
{
    Mediator_Fld *pFld;

    void (* PlayerAWin)(Mediator *pInst, double dblMoney);
    void (* PlayerBWin)(Mediator *pInst, double dblMoney);
};

Mediator *Mediator_New(apr_pool_t *pSupPool, ICardPlayer *pPlayerA, ICardPlayer *pPlayerB);
void Mediator_Free(Mediator **ppInst);

#endif // !MEDIATOR_H
