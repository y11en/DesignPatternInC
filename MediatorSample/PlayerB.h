
#include <apr_pools.h>
#include "ICardPlayer.h"


#ifndef PLAYERB_H
#define PLAYERB_H

typedef struct PlayerB_Fld PlayerB_Fld;
typedef struct PlayerB PlayerB;

struct PlayerB
{
    PlayerB_Fld *pFld;
};

PlayerB *PlayerB_New(apr_pool_t *pSupPool);
ICardPlayer *PlayerB2ICardPlayer(PlayerB *pInst);
void PlayerB_Free(PlayerB **ppInst);

#endif // !PLAYERB_H
