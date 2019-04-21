
#include "Caretaker.h"

struct Caretaker_Fld
{
    apr_pool_t *m_pPool;

    Memento *m_pMemento;
};

static Memento *GetMemento(Caretaker *pInst)
{
    return pInst->pFld->m_pMemento;
}

static void SetMemento(Caretaker *pInst, Memento *pMemnto)
{
    pInst->pFld->m_pMemento = pMemnto;
}

Caretaker * Caretaker_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Caretaker *pInst = apr_palloc(pPool, sizeof(Caretaker));

    pInst->pFld = apr_palloc(pPool, sizeof(Caretaker_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_pMemento = NULL;

    pInst->GetMemento = GetMemento;
    pInst->SetMemento = SetMemento;

    return pInst;
}

void Caretaker_Free(Caretaker ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
