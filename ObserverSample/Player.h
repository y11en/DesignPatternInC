
#include <apr_pools.h>
#include "IObserver.h"


#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_Fld Player_Fld;
typedef struct Player Player;

struct Player
{
	Player_Fld *pFld;
};

Player *Player_New(apr_pool_t *pSupPool, const char *pName);
IObserver *Player2IObserver(Player *pInst);
void Player_Free(Player **ppInst);

#endif // !PLAYER_H
