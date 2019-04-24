
#include <apr_pools.h>
#include "IApprover.h"


#ifndef APPROVERPRESIDENT_H
#define APPROVERPRESIDENT_H

typedef struct ApproverPresident_Fld ApproverPresident_Fld;
typedef struct ApproverPresident ApproverPresident;

struct ApproverPresident
{
	ApproverPresident_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

ApproverPresident *ApproverPresident_New(apr_pool_t *pSupPool, const char *pName);
IApprover *ApproverPresident2IApprover(ApproverPresident *pInst);
void ApproverPresident_Free(ApproverPresident **ppInst);

#endif // !APPROVERPRESIDENT_H
