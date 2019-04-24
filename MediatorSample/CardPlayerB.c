
#include "CardPlayerB.h"
#include "Mediator.h"

struct CardPlayerB_Fld
{
    apr_pool_t *m_pPool;

    ICardPlayer m_player;

    double m_dblMoney;
};

static void Free(ICardPlayer **ppCardPlayer)
{
	CardPlayerB_Free(&(CardPlayerB *)(*ppCardPlayer)->pImplicit);
    *ppCardPlayer = NULL;
}

static double GetMoney(ICardPlayer *pCardPlayer)
{
	CardPlayerB *pInst = (CardPlayerB *)pCardPlayer->pImplicit;
    return pInst->pFld->m_dblMoney;
}

static void SetMoney(ICardPlayer *pCardPlayer, double dblMoney)
{
	CardPlayerB *pInst = (CardPlayerB *)pCardPlayer->pImplicit;
    pInst->pFld->m_dblMoney = dblMoney;
}

static void ChangeMoney(ICardPlayer *pCardPlayer, double dblMoney, Mediator *pMediator)
{
	CardPlayerB *pInst = (CardPlayerB *)pCardPlayer->pImplicit;
    pMediator->PlayerBWin(pMediator, dblMoney);
}

CardPlayerB * CardPlayerB_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	CardPlayerB *pInst = apr_palloc(pPool, sizeof(CardPlayerB));

    pInst->pFld = apr_palloc(pPool, sizeof(CardPlayerB_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_player.pImplicit = pInst;
    pInst->pFld->m_player.Free = Free;

    pInst->pFld->m_player.GetMoney = GetMoney;
    pInst->pFld->m_player.SetMoney = SetMoney;
    pInst->pFld->m_player.ChangeMoney = ChangeMoney;

    pInst->pFld->m_dblMoney = 0;

    return pInst;
}

ICardPlayer * CardPlayerB2ICardPlayer(CardPlayerB * pInst)
{
    return &(pInst->pFld->m_player);
}

void CardPlayerB_Free(CardPlayerB ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
