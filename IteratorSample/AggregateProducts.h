
#include <apr_pools.h>
#include "IAggregate.h"


#ifndef AGGREGATEPRODUCTS_H
#define AGGREGATEPRODUCTS_H

typedef struct AggregateProducts_Fld AggregateProducts_Fld;
typedef struct AggregateProducts AggregateProducts;

struct AggregateProducts
{
	AggregateProducts_Fld *pFld;
};

AggregateProducts *AggregateProducts_New(apr_pool_t *pSupPool, RING(TxObject) *pProducts);
IAggregate *AggregateProducts2IAggregate(AggregateProducts *pInst);
void AggregateProducts_Free(AggregateProducts **ppInst);

#endif // !AGGREGATEPRODUCTS_H
