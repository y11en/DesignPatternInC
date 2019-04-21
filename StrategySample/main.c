
#include <stdio.h>
#include <apr_pools.h>
#include "MovieTicket.h"
#include "IDiscount.h"
#include "DiscountVIP.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    MovieTicket *pTicket = MovieTicket_New(pMemPool);
    IDiscount *pDiscount = DiscountVIP2IDiscount(DiscountVIP_New(pMemPool));
    double dblOriginPrice = 60.0;
    double dblCurrentPrice = -1;

    pTicket->SetPrice(pTicket, dblOriginPrice);
    printf("原始票价：%f.\n", dblOriginPrice);
    puts("--------------------------------------");
    pTicket->SetDiscount(pTicket, pDiscount);
    dblCurrentPrice = pTicket->GetPrice(pTicket);
    printf("折后价：%f.\n", dblCurrentPrice);

    pDiscount->Free(&pDiscount);
    MovieTicket_Free(&pTicket);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}