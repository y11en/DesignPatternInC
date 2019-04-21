
#include <stdio.h>
#include <apr_pools.h>
#include "IEncryptFacade.h"
#include "EnhancedEncryptFacade.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    IEncryptFacade *pFacade = EnhancedEncryptFacade2IEncryptFacade(EnhancedEncryptFacade_New(pMemPool));
    pFacade->ToEncryptFile(pFacade, "D:/Inspiration/Development/Workspace/C/DP/Debug/frm.txt", "D:/Inspiration/Development/Workspace/C/DP/Debug/dst.txt");

    pFacade->Free(&pFacade);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}