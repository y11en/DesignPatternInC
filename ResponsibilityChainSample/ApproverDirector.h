
#include <apr_pools.h>
#include "IApprover.h"


#ifndef APPROVERDIRECTOR_H
#define APPROVERDIRECTOR_H

typedef struct ApproverDirector_Fld ApproverDirector_Fld;
typedef struct ApproverDirector ApproverDirector;

struct ApproverDirector
{
	ApproverDirector_Fld *pFld;
};

ApproverDirector *ApproverDirector_New(apr_pool_t *pSupPool, const char *pName);
IApprover *ApproverDirector2IApprover(ApproverDirector *pInst);
void ApproverDirector_Free(ApproverDirector **ppInst);

#endif // !APPROVERDIRECTOR_H
