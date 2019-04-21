
#include <apr_pools.h>
#include "IDiscount.h"


#ifndef DISCOUNTVIP_H
#define DISCOUNTVIP_H

typedef struct DiscountVIP_Fld DiscountVIP_Fld;
typedef struct DiscountVIP DiscountVIP;

struct DiscountVIP
{
    DiscountVIP_Fld *pFld;
};

DiscountVIP *DiscountVIP_New(apr_pool_t *pSupPool);
IDiscount *DiscountVIP2IDiscount(DiscountVIP *pInst);
void DiscountVIP_Free(DiscountVIP **ppInst);

#endif // !DISCOUNTVIP_H
