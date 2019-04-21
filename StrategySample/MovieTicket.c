
#include "MovieTicket.h"

struct MovieTicket_Fld
{
	apr_pool_t *m_pPool;

	IDiscount *m_pDiscount;

	double m_dblPrice;
};

static void SetDiscount(MovieTicket *pInst, IDiscount *pDiscount)
{
	pInst->pFld->m_pDiscount = pDiscount;
}

static double GetPrice(MovieTicket *pInst)
{
	//return pInst->pFld->m_dblPrice;
    return pInst->pFld->m_pDiscount->Calculate(pInst->pFld->m_pDiscount, pInst->pFld->m_dblPrice);
}

static void SetPrice(MovieTicket *pInst, double dblPrice)
{
	pInst->pFld->m_dblPrice = dblPrice;
}

MovieTicket * MovieTicket_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	MovieTicket *pInst = apr_palloc(pPool, sizeof(MovieTicket));

	pInst->pFld = apr_palloc(pPool, sizeof(MovieTicket_Fld));
	pInst->pFld->m_pPool = pPool;

	pInst->pFld->m_pDiscount = NULL;
	pInst->pFld->m_dblPrice = 0;

	pInst->SetDiscount = SetDiscount;
	pInst->GetPrice = GetPrice;
	pInst->SetPrice = SetPrice;

	return pInst;
}

void MovieTicket_Free(MovieTicket ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
