
#include <apr_pools.h>

#ifndef EMPEROR_H
#define EMPEROR_H

typedef struct Emperor_Fld Emperor_Fld;
typedef struct Emperor Emperor;

struct Emperor
{
    Emperor_Fld *pFld;

    void (* Say)(Emperor *pInst);
};

Emperor *GetEmperorInstance(apr_pool_t *pMemPool);
void Emperor_Free(Emperor **ppInst);

#endif // !EMPEROR_H
