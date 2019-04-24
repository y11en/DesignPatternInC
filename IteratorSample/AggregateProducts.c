
#include "IteratorProduct.h"
#include "AggregateProducts.h"

struct AggregateProducts_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IAggregate m_aggregate;

    //产品环链表
    RING(TxObject) *m_pProducts;

    //迭代器
    IIterator *m_pIterator;
};

static void Free(IAggregate **ppAggregate)
{
	AggregateProducts_Free(&(AggregateProducts *)(*ppAggregate)->pImplicit);
    *ppAggregate = NULL;
}

static RING(TxObject) *GetTxObjects(IAggregate *pAggregate)
{
	AggregateProducts *pInst = (AggregateProducts *)pAggregate->pImplicit;
    return pInst->pFld->m_pProducts;
}

static void SetTxObjects(IAggregate *pAggregate, RING(TxObject) *pTxObjects)
{
	AggregateProducts *pInst = (AggregateProducts *)pAggregate->pImplicit;
    pInst->pFld->m_pProducts = pTxObjects;
}

static IIterator *CreateIterator(IAggregate *pAggregate)
{
	AggregateProducts *pInst = (AggregateProducts *)pAggregate->pImplicit;
    return pInst->pFld->m_pIterator;
}

AggregateProducts * AggregateProducts_New(apr_pool_t * pSupPool, RING(TxObject) *pProducts)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	AggregateProducts *pInst = apr_palloc(pPool, sizeof(AggregateProducts));

    pInst->pFld = apr_palloc(pPool, sizeof(AggregateProducts_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_aggregate.pImplicit = pInst;
    pInst->pFld->m_aggregate.Free = Free;

    pInst->pFld->m_aggregate.GetTxObjects = GetTxObjects;
    pInst->pFld->m_aggregate.SetTxObjects = SetTxObjects;
    pInst->pFld->m_aggregate.CreateIterator = CreateIterator;

    pInst->pFld->m_pProducts = pProducts;
    pInst->pFld->m_pIterator = IteratorProduct2IIterator(IteratorProduct_New(pInst->pFld->m_pPool, pInst->pFld->m_pProducts));

    return pInst;
}

IAggregate * AggregateProducts2IAggregate(AggregateProducts * pInst)
{
    return &(pInst->pFld->m_aggregate);
}

void AggregateProducts_Free(AggregateProducts ** ppInst)
{
    (*ppInst)->pFld->m_pIterator->Free(&((*ppInst)->pFld->m_pIterator));

    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
