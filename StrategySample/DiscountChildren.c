
#include <stdio.h>
#include "DiscountChildren.h"

#define DISCOUNT 10

struct DiscountChildren_Fld
{
	apr_pool_t *m_pPool;

	IDiscount m_discount;
};

static void Free(IDiscount **ppDiscount)
{
	DiscountChildren_Free(&(DiscountChildren *)(*ppDiscount)->pImplicit);
	*ppDiscount = NULL;
}

static double Calculate(IDiscount *pDiscount, double dblPrice)
{
	//DiscountChildren *pInst = (DiscountChildren *)pDiscount->pImplicit;

	puts("¶ùÍ¯Æ±.");
	return dblPrice - DISCOUNT;
}

DiscountChildren * DiscountChildren_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	DiscountChildren *pInst = apr_palloc(pPool, sizeof(DiscountChildren));

	pInst->pFld = apr_palloc(pPool, sizeof(DiscountChildren_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_discount.pImplicit = pInst;
	pInst->pFld->m_discount.Free = Free;

	pInst->pFld->m_discount.Calculate = Calculate;

	return pInst;
}

IDiscount * DiscountChildren2IDiscount(DiscountChildren * pInst)
{
	return &(pInst->pFld->m_discount);
}

void DiscountChildren_Free(DiscountChildren ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
