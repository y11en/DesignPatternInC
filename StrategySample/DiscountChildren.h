
#include <apr_pools.h>
#include "IDiscount.h"


#ifndef DISCOUNTCHILDREN_H
#define DISCOUNTCHILDREN_H

typedef struct DiscountChildren_Fld DiscountChildren_Fld;
typedef struct DiscountChildren DiscountChildren;

struct DiscountChildren
{
	DiscountChildren_Fld *pFld;
};

DiscountChildren *DiscountChildren_New(apr_pool_t *pSupPool);
IDiscount *DiscountChildren2IDiscount(DiscountChildren *pInst);
void DiscountChildren_Free(DiscountChildren **ppInst);

#endif // !DISCOUNTCHILDREN_H