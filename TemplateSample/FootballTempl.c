
#include <stdio.h>
#include "ExtendTemplate.h"

static void Initialize(Game *pGame)
{
	puts("Football Game Initialized! Start playing.");
}

static void Start(Game *pGame)
{
	puts("Football Game Started. Enjoy the game!");
}

static void End(Game *pGame)
{
	puts("Football Game Finished!");
}

Game * WithFootballTempl(Game * pGame)
{
	pGame->Initialize = Initialize;
	pGame->Start = Start;
	pGame->End = End;

	return pGame;
}