
#include <stdio.h>
#include "ExtendTemplate.h"

static void Initialize(Game *pGame)
{
	puts("Cricket Game Initialized! Start playing.");
}

static void Start(Game *pGame)
{
	puts("Cricket Game Started. Enjoy the game!");
}

static void End(Game *pGame)
{
	puts("Cricket Game Finished!");
}

Game * WithCricketTempl(Game * pGame)
{
	pGame->Initialize = Initialize;
	pGame->Start = Start;
	pGame->End = End;

	return pGame;
}