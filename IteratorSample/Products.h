
#include <apr_pools.h>
#include "IAggregate.h"


#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

typedef struct Products_Fld Products_Fld;
typedef struct Products Products;

struct Products
{
    Products_Fld *pFld;
};

Products *Products_New(apr_pool_t *pSupPool, RING(TxObject) *pProducts);
IAggregate *Products2IAggregate(Products *pInst);
void Products_Free(Products **ppInst);

#endif // !PRODUCTLIST_H
