
#include "IteratorProduct.h"

struct IteratorProduct_Fld
{
    apr_pool_t *m_pPool;

    IIterator m_iterator;

    RING(TxObject) *m_pProducts;
    //正向遍历游标
    RING_ELEM(TxObject) *m_pCursorPositive;
    //逆向遍历游标
    RING_ELEM(TxObject) *m_pCursorNegative;
};

static void Free(IIterator **ppIterator)
{
    IteratorProduct_Free(&(IteratorProduct *)(*ppIterator)->pImplicit);
    *ppIterator = NULL;
}

static void Next(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    pInst->pFld->m_pCursorPositive = APR_RING_NEXT(pInst->pFld->m_pCursorPositive, RING_LINK);
}

static bool IsLast(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    return pInst->pFld->m_pCursorPositive == APR_RING_SENTINEL(pInst->pFld->m_pProducts, RING_ELEM(TxObject), RING_LINK);
}

static void Previous(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    pInst->pFld->m_pCursorNegative = APR_RING_PREV(pInst->pFld->m_pCursorNegative, RING_LINK);
}

static bool IsFirst(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    return pInst->pFld->m_pCursorNegative == APR_RING_SENTINEL(pInst->pFld->m_pProducts, RING_ELEM(TxObject), RING_LINK);
}

static TxObject *GetNext(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    return pInst->pFld->m_pCursorPositive->pInst;
}

static TxObject *GetPrevious(IIterator *pIterator)
{
    IteratorProduct *pInst = (IteratorProduct *)pIterator->pImplicit;
    return pInst->pFld->m_pCursorNegative->pInst;
}

IteratorProduct * IteratorProduct_New(apr_pool_t * pSupPool, RING(TxObject)* pProducts)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    IteratorProduct *pInst = apr_palloc(pPool, sizeof(IteratorProduct));

    pInst->pFld = apr_palloc(pPool, sizeof(IteratorProduct_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_iterator.pImplicit = pInst;
    pInst->pFld->m_iterator.Free = Free;

    pInst->pFld->m_iterator.Next = Next;
    pInst->pFld->m_iterator.IsLast = IsLast;
    pInst->pFld->m_iterator.Previous = Previous;
    pInst->pFld->m_iterator.IsFirst = IsFirst;
    pInst->pFld->m_iterator.GetNextItem = GetNext;
    pInst->pFld->m_iterator.GetPreviousItem = GetPrevious;

    pInst->pFld->m_pProducts = pProducts;
    pInst->pFld->m_pCursorPositive = APR_RING_FIRST(pInst->pFld->m_pProducts);
    pInst->pFld->m_pCursorNegative = APR_RING_LAST(pInst->pFld->m_pProducts);

    return pInst;
}

IIterator * IteratorProduct2IIterator(IteratorProduct * pInst)
{
    return &(pInst->pFld->m_iterator);
}

void IteratorProduct_Free(IteratorProduct **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
