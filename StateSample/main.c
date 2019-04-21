
#include <stdlib.h>
#include <stdio.h>
#include <apr_pools.h>
#include "Account.h"


int main(int argc, char **argv)
{
    for (size_t i = 0; i < 10000; i++)
    {
        apr_pool_t *pMemPool;

        apr_initialize();

        apr_pool_create(&pMemPool, NULL);

        Account *pAccnt = Account_New(pMemPool, 0.0, "¶ÎÓþ");
        pAccnt->Deposit(pAccnt, 1000);
        pAccnt->Withdraw(pAccnt, 2000);
        pAccnt->Deposit(pAccnt, 3000);
        pAccnt->Withdraw(pAccnt, 4000);
        pAccnt->Withdraw(pAccnt, 1000);
        pAccnt->CalcInterest(pAccnt);

        Account_Free(&pAccnt);

        apr_pool_destroy(pMemPool);

        apr_terminate();
    }

    return EXIT_SUCCESS;
}