
#include <stdio.h>
#include <apr_pools.h>
#include "Caretaker.h"
#include "Memento.h"
#include "Chessman.h"


void output(Chessman *pChessman, apr_pool_t *pPool)
{
    printf("棋子%s的当前的位置为：第%d行，第%d列。\n", pChessman->GetLabel(pChessman, pPool), pChessman->GetX(pChessman), pChessman->GetY(pChessman));
}

int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    Caretaker *pCaretaker = Caretaker_New(pMemPool);
    Chessman *pChessman = Chessman_New(pMemPool, "车", 1, 1);
    output(pChessman, pMemPool);

    Memento *pOut = Memento_New(pMemPool, "-", 0, 0);
    pCaretaker->SetMemento(pCaretaker, pChessman->Save(pChessman, pMemPool, pOut));//保存状态
    pChessman->SetY(pChessman, 4);
    output(pChessman, pMemPool);

    pCaretaker->SetMemento(pCaretaker, pChessman->Save(pChessman, pMemPool, pOut));//保存状态
    output(pChessman, pMemPool);

    pChessman->SetY(pChessman, 5);
    output(pChessman, pMemPool);

    puts("悔棋---------");
    pChessman->Restore(pChessman, pCaretaker->GetMemento(pCaretaker));//恢复状态
    output(pChessman, pMemPool);

	Memento_Free(&pOut);
	Chessman_Free(&pChessman);
	Caretaker_Free(&pCaretaker);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}