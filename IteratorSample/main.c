
#include <stdio.h>
#include <apr_pools.h>
#include <apr_strings.h>
#include "TxObjectRing.h"
#include "IAggregate.h"
#include "AggregateProducts.h"
#include "IIterator.h"
#include "IteratorProduct.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    RING(TxObject) *pRing = apr_palloc(pMemPool, sizeof(RING(TxObject)));
    APR_RING_INIT(pRing, RING_ELEM(TxObject), RING_LINK);

    RING_ELEM(TxObject) *pElem1 = apr_palloc(pMemPool, sizeof(RING_ELEM(TxObject)));
    pElem1->pInst = apr_pstrdup(pMemPool, "倚天剑");
    RING_ELEM(TxObject) *pElem2 = apr_palloc(pMemPool, sizeof(RING_ELEM(TxObject)));
    pElem2->pInst = apr_pstrdup(pMemPool, "屠龙刀");
    RING_ELEM(TxObject) *pElem3 = apr_palloc(pMemPool, sizeof(RING_ELEM(TxObject)));
    pElem3->pInst = apr_pstrdup(pMemPool, "断肠草");
    RING_ELEM(TxObject) *pElem4 = apr_palloc(pMemPool, sizeof(RING_ELEM(TxObject)));
    pElem4->pInst = apr_pstrdup(pMemPool, "葵花宝典");
    RING_ELEM(TxObject) *pElem5 = apr_palloc(pMemPool, sizeof(RING_ELEM(TxObject)));
    pElem5->pInst = apr_pstrdup(pMemPool, "四十二章经");

    APR_RING_INSERT_TAIL(pRing, pElem1, RING_ELEM(TxObject), RING_LINK);
    APR_RING_INSERT_TAIL(pRing, pElem2, RING_ELEM(TxObject), RING_LINK);
    APR_RING_INSERT_TAIL(pRing, pElem3, RING_ELEM(TxObject), RING_LINK);
    APR_RING_INSERT_TAIL(pRing, pElem4, RING_ELEM(TxObject), RING_LINK);
    APR_RING_INSERT_TAIL(pRing, pElem5, RING_ELEM(TxObject), RING_LINK);

    IAggregate *pAggregate = AggregateProducts2IAggregate(AggregateProducts_New(pMemPool, pRing));
    IIterator *pIterator = pAggregate->CreateIterator(pAggregate);

    puts("正向遍历.");
    while (!pIterator->IsLast(pIterator))
    {
        printf("%s, ", (char *)pIterator->GetNextItem(pIterator));
        pIterator->Next(pIterator);
    }
    printf("\n");
    puts("--------------------------------------");
    puts("逆向遍历.");
    while (!pIterator->IsFirst(pIterator))
    {
        printf("%s, ", (char *)pIterator->GetPreviousItem(pIterator));
        pIterator->Previous(pIterator);
    }

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}
