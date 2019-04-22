
#include <apr_pools.h>


#ifndef GAME_H
#define GAME_H

typedef struct Game_Fld Game_Fld;
typedef struct Game Game;

struct Game
{
	Game_Fld *pFld;

	void (* Initialize)(Game *pInst);
	void (* Play)(Game *pInst);
	void (* Start)(Game *pInst);
	void (* End)(Game *pInst);
};

Game *Game_New(apr_pool_t *pSupPool);
void Game_Free(Game **ppInst);

#endif // !GAME_H
