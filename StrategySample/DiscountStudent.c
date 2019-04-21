
#include <stdio.h>
#include "DiscountStudent.h"

#define DISCOUNT 0.8

struct DiscountStudent_Fld
{
    apr_pool_t *m_pPool;

    IDiscount m_discount;
};

static void Free(IDiscount **ppDiscount)
{
    DiscountStudent_Free(&(DiscountStudent *)(*ppDiscount)->pImplicit);
    *ppDiscount = NULL;
}

static double Calculate(IDiscount *pDiscount, double dblPrice)
{
    puts("Ñ§ÉúÆ±.");
    return dblPrice * DISCOUNT;
}

DiscountStudent * DiscountStudent_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DiscountStudent *pInst = apr_palloc(pPool, sizeof(DiscountStudent));
    
    pInst->pFld = apr_palloc(pPool, sizeof(DiscountStudent_Fld));
    pInst->pFld->m_discount.pImplicit = pInst;
    pInst->pFld->m_discount.Free = Free;

    pInst->pFld->m_discount.Calculate = Calculate;

    return pInst;
}

IDiscount * DiscountStudent2IDiscount(DiscountStudent * pInst)
{
    return &(pInst->pFld->m_discount);
}

void DiscountStudent_Free(DiscountStudent ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
