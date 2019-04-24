
#include <apr_pools.h>
#include "ICardPlayer.h"


#ifndef CARDPLAYERA_H
#define CARDPLAYERA_H

typedef struct CardPlayerA_Fld CardPlayerA_Fld;
typedef struct CardPlayerA CardPlayerA;

struct CardPlayerA
{
	CardPlayerA_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

CardPlayerA *CardPlayerA_New(apr_pool_t *pSupPool);
ICardPlayer *CardPlayerA2ICardPlayer(CardPlayerA *pInst);
void CardPlayerA_Free(CardPlayerA **ppInst);

#endif // !CARDPLAYERA_H