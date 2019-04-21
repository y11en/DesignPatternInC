
#include <apr_pools.h>


#ifndef PURCHASEREQUEST_H
#define PURCHASEREQUEST_H

typedef struct PurchaseRequest_Fld PurchaseRequest_Fld;
typedef struct PurchaseRequest PurchaseRequest;

struct PurchaseRequest
{
    PurchaseRequest_Fld *pFld;

    double (* GetAmount)(PurchaseRequest *pInst);
    void (* SetAmount)(PurchaseRequest *pInst, double dblAmount);
    int (* GetPurchaseCode)(PurchaseRequest *pInst);
    void (* SetPurchaseCode)(PurchaseRequest *pInst, int nPurchaseCode);
    char *(* GetPurpose)(PurchaseRequest *pInst, apr_pool_t *pPool);
    void (* SetPurpose)(PurchaseRequest *pInst, const char *pPurpose);
};

PurchaseRequest *PurchaseRequest_New(apr_pool_t *pSupPool, double dblAmount, int nPurchaseCode, const char *pPurpose);
void PurchaseRequest_Free(PurchaseRequest **ppInst);

#endif // !PURCHASEREQUEST_H
