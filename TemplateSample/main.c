
#include <apr_pools.h>
#include "Game.h"
#include "ExtendTemplate.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;

	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

	Game *pGame = Game_New(pMemPool);
	pGame->Play(pGame);
	puts("-------------------------------------");
	pGame = WithCricketTempl(pGame);
	pGame->Play(pGame);
	puts("-------------------------------------");
	pGame = WithFootballTempl(pGame);
	pGame->Play(pGame);
	puts("-------------------------------------");
	Game_Free(&pGame);

	apr_pool_destroy(pMemPool);

	apr_terminate();

	return EXIT_SUCCESS;
}