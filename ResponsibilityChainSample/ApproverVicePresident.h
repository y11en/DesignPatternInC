
#include <apr_pools.h>
#include "IApprover.h"


#ifndef APPROVERVICEPRESIDENT_H
#define APPROVERVICEPRESIDENT_H

typedef struct ApproverVicePresident_Fld ApproverVicePresident_Fld;
typedef struct ApproverVicePresident ApproverVicePresident;

struct ApproverVicePresident
{
	ApproverVicePresident_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

ApproverVicePresident *ApproverVicePresident_New(apr_pool_t *pSupPool, const char *pName);
IApprover *ApproverVicePresident2IApprover(ApproverVicePresident *pInst);
void ApproverVicePresident_Free(ApproverVicePresident **ppInst);

#endif // !APPROVERVICEPRESIDENT_H
