
#include <stdio.h>
#include "Game.h"

struct Game_Fld
{
	apr_pool_t *m_pPool;
};

static void Initialize(Game *pInst)
{
	puts("游戏初始化完成。");
}

static void Play(Game *pInst)
{
	pInst->Initialize(pInst);

	pInst->Start(pInst);
	pInst->End(pInst);
}

static void Start(Game *pInst)
{
	puts("游戏开始。");
}

static void End(Game *pInst)
{
	puts("游戏结束.");
}

Game * Game_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Game *pInst = apr_palloc(pPool, sizeof(Game));

	pInst->pFld = apr_palloc(pPool, sizeof(Game_Fld));
	pInst->pFld->m_pPool = pPool;

	pInst->Initialize = Initialize;
	pInst->Play = Play;
	pInst->Start = Start;
	pInst->End = End;

	return pInst;
}

void Game_Free(Game ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
