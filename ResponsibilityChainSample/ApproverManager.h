
#include <apr_pools.h>
#include "IApprover.h"


#ifndef APPROVERMANAGER_H
#define APPROVERMANAGER_H

typedef struct ApproverManager_Fld ApproverManager_Fld;
typedef struct ApproverManager ApproverManager;

struct ApproverManager
{
	ApproverManager_Fld *pFld;
};

ApproverManager *ApproverManager_New(apr_pool_t *pSupPool, const char *pName);
IApprover *ApproverManager2IApprover(ApproverManager *pInst);
void ApproverManager_Free(ApproverManager **ppInst);

#endif // !APPROVERMANAGER_H
