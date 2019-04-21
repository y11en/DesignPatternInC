
#include <apr_pools.h>
#include "IApprover.h"


#ifndef VICEPRESIDENT_H
#define VICEPRESIDENT_H

typedef struct VicePresident_Fld VicePresident_Fld;
typedef struct VicePresident VicePresident;

struct VicePresident
{
    VicePresident_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

VicePresident *VicePresident_New(apr_pool_t *pSupPool, const char *pName);
IApprover *VicePresident2IApprover(VicePresident *pInst);
void VicePresident_Free(VicePresident **ppInst);

#endif // !VICEPRESIDENT_H
