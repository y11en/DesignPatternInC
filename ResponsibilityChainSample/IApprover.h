
#include "PurchaseRequest.h"

#ifndef IAPPROVER_H
#define IAPPROVER_H

typedef struct IApprover IApprover;

struct IApprover
{
    void *pImplicit;
    void (* SetSuccessor)(IApprover *pApprover, IApprover *pSuccessor);
    void (* ProcessRequest)(IApprover *pApprover, PurchaseRequest *pRequest);
    void (* Free)(IApprover **ppApprover);
};

#endif // !IAPPROVER_H
