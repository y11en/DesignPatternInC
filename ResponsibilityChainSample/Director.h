
#include <apr_pools.h>
#include "IApprover.h"


#ifndef DIRECTOR_H
#define DIRECTOR_H

typedef struct Director_Fld Director_Fld;
typedef struct Director Director;

struct Director
{
    Director_Fld *pFld;
};

Director *Director_New(apr_pool_t *pSupPool, const char *pName);
IApprover *Director2IApprover(Director *pInst);
void Director_Free(Director **ppInst);

#endif // !DIRECTOR_H
