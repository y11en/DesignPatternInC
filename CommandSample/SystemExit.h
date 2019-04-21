
#include <apr_pools.h>


#ifndef SYSTEMEXIT_H
#define SYSTEMEXIT_H

typedef struct SystemExit_Fld SystemExit_Fld;
typedef struct SystemExit SystemExit;

struct SystemExit
{
    SystemExit_Fld *pFld;

    void (* Exit)(SystemExit *pInst);
};

SystemExit *SystemExit_New(apr_pool_t *pSupPool);
void SystemExit_Free(SystemExit **ppInst);

#endif // !SYSTEMEXIT_H
