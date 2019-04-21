
#include <stdio.h>
#include "DiscountVIP.h"

#define DISCOUNT 0.5

struct DiscountVIP_Fld
{
    apr_pool_t *m_pPool;

    IDiscount m_discount;
};

static void Free(IDiscount **ppDiscount)
{
    DiscountVIP_Free(&(DiscountVIP *)(*ppDiscount)->pImplicit);
    *ppDiscount = NULL;
}

static double Calculate(IDiscount *pDiscount, double dblPrice)
{
    puts("VIP票.");
    puts("增加积分.");
    return dblPrice * DISCOUNT;
}

DiscountVIP * DiscountVIP_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DiscountVIP *pInst = apr_palloc(pPool, sizeof(DiscountVIP));

    pInst->pFld = apr_palloc(pPool, sizeof(DiscountVIP_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_discount.pImplicit = pInst;
    pInst->pFld->m_discount.Free = Free;

    pInst->pFld->m_discount.Calculate = Calculate;

    return pInst;
}

IDiscount * DiscountVIP2IDiscount(DiscountVIP * pInst)
{
    return &(pInst->pFld->m_discount);
}

void DiscountVIP_Free(DiscountVIP ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
