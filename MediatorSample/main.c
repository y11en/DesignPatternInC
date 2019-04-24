
#include <stdio.h>
#include <apr_pools.h>
#include "Mediator.h"
#include "ICardPlayer.h"
#include "CardPlayerA.h"
#include "CardPlayerB.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    ICardPlayer *pA = CardPlayerA2ICardPlayer(CardPlayerA_New(pMemPool));
    pA->SetMoney(pA, 20);
    ICardPlayer *pB = CardPlayerB2ICardPlayer(CardPlayerB_New(pMemPool));
    pB->SetMoney(pB, 20);

    Mediator *pMediator = Mediator_New(pMemPool, pA, pB);

    printf("初始时，A的钱是：%f。\n", pA->GetMoney(pA));
    printf("初始时，B的钱时：%f。\n", pB->GetMoney(pB));

    pA->ChangeMoney(pA, 5, pMediator);
    printf("A赢5块钱后，A的钱是：%f。\n", pA->GetMoney(pA));
    printf("A赢5块钱后，B的钱是：%f。\n", pB->GetMoney(pB));
    pB->ChangeMoney(pB, 8, pMediator);
    printf("B赢8块钱后，A的钱是：%f。\n", pA->GetMoney(pA));
    printf("B赢8块钱后，B的钱是：%f。\n", pB->GetMoney(pB));

    pA->Free(&pA);
    pB->Free(&pB);
    Mediator_Free(&pMediator);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}
