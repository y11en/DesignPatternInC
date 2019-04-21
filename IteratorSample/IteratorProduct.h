
#include <apr_pools.h>
#include "TxObjectRing.h"
#include "IIterator.h"


#ifndef ITERATORPRODUCT_H
#define ITERATORPRODUCT_H

typedef struct IteratorProduct_Fld IteratorProduct_Fld;
typedef struct IteratorProduct IteratorProduct;

struct IteratorProduct
{
    IteratorProduct_Fld *pFld;
};

IteratorProduct *IteratorProduct_New(apr_pool_t *pSupPool, RING(TxObject) *pProducts);
IIterator *IteratorProduct2IIterator(IteratorProduct *pInst);
void IteratorProduct_Free(IteratorProduct **ppInst);

#endif // !ITERATORPRODUCT_H
