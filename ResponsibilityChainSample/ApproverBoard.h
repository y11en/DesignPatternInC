
#include <apr_pools.h>
#include "IApprover.h"


#ifndef APPROVERBOARD_H
#define APPROVERBOARD_H

typedef struct ApproverBoard_Fld ApproverBoard_Fld;
typedef struct ApproverBoard ApproverBoard;

struct ApproverBoard
{
	ApproverBoard_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

ApproverBoard *ApproverBoard_New(apr_pool_t *pSupPool, const char *pName);
IApprover *ApproverBoard2IApprover(ApproverBoard *pInst);
void ApproverBoard_Free(ApproverBoard **ppInst);

#endif // !APPROVERBOARD_H

