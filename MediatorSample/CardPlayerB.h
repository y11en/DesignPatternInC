
#include <apr_pools.h>
#include "ICardPlayer.h"


#ifndef CARDPLAYERB_H
#define CARDPLAYERB_H

typedef struct CardPlayerB_Fld CardPlayerB_Fld;
typedef struct CardPlayerB CardPlayerB;

struct CardPlayerB
{
	CardPlayerB_Fld *pFld;
};

CardPlayerB *CardPlayerB_New(apr_pool_t *pSupPool);
ICardPlayer *CardPlayerB2ICardPlayer(CardPlayerB *pInst);
void CardPlayerB_Free(CardPlayerB **ppInst);

#endif // !CARDPLAYERB_H
