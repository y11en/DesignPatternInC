
#include "Mediator.h"

struct Mediator_Fld
{
    apr_pool_t *m_pPool;

    ICardPlayer *m_pPlayerA;
    ICardPlayer *m_pPlayerB;
};

static void PlayerAWin(Mediator *pInst, double dblMoney)
{
    ICardPlayer *pA = pInst->pFld->m_pPlayerA;
    ICardPlayer *pB = pInst->pFld->m_pPlayerB;

    pA->SetMoney(pA, pA->GetMoney(pA) + dblMoney);
    pB->SetMoney(pB, pB->GetMoney(pB) - dblMoney);
}

static void PlayerBWin(Mediator *pInst, double dblMoney)
{
    ICardPlayer *pA = pInst->pFld->m_pPlayerA;
    ICardPlayer *pB = pInst->pFld->m_pPlayerB;

    pA->SetMoney(pA, pA->GetMoney(pA) - dblMoney);
    pB->SetMoney(pB, pB->GetMoney(pB) + dblMoney);
}

Mediator * Mediator_New(apr_pool_t *pSupPool, ICardPlayer *pPlayerA, ICardPlayer *pPlayerB)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Mediator *pInst = apr_palloc(pPool, sizeof(Mediator));

    pInst->pFld = apr_palloc(pPool, sizeof(Mediator_Fld));
    pInst->pFld->m_pPool = pPool;
    
    pInst->pFld->m_pPlayerA = pPlayerA;
    pInst->pFld->m_pPlayerB = pPlayerB;

    pInst->PlayerAWin = PlayerAWin;
    pInst->PlayerBWin = PlayerBWin;

    return pInst;
}

void Mediator_Free(Mediator ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
