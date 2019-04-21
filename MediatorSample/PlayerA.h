
#include <apr_pools.h>
#include "ICardPlayer.h"


#ifndef PLAYERA_H
#define PLAYERA_H

typedef struct PlayerA_Fld PlayerA_Fld;
typedef struct PlayerA PlayerA;

struct PlayerA
{
    PlayerA_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

PlayerA *PlayerA_New(apr_pool_t *pSupPool);
ICardPlayer *PlayerA2ICardPlayer(PlayerA *pInst);
void PlayerA_Free(PlayerA **ppInst);

#endif // !PLAYERA_H