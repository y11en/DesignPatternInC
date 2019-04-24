
#include "CardPlayerA.h"
#include "Mediator.h"

struct CardPlayerA_Fld
{
    apr_pool_t *m_pPool;

    ICardPlayer m_player;

    double m_dblMoney;
};

static void Free(ICardPlayer **ppCardPlayer)
{
	CardPlayerA_Free(&(CardPlayerA *)(*ppCardPlayer)->pImplicit);
    *ppCardPlayer = NULL;
}

static double GetMoney(ICardPlayer *pCardPlayer)
{
	CardPlayerA *pInst = (CardPlayerA *)pCardPlayer->pImplicit;
    return pInst->pFld->m_dblMoney;
}

static void SetMoney(ICardPlayer *pCardPlayer, double dblMoney)
{
	CardPlayerA *pInst = (CardPlayerA *)pCardPlayer->pImplicit;
    pInst->pFld->m_dblMoney = dblMoney;
}

static void ChangeMoney(ICardPlayer *pCardPlayer, double dblMoney, Mediator *pMediator)
{
	CardPlayerA *pInst = (CardPlayerA *)pCardPlayer->pImplicit;
    pMediator->PlayerAWin(pMediator, dblMoney);
}

CardPlayerA * CardPlayerA_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	CardPlayerA *pInst = apr_palloc(pPool, sizeof(CardPlayerA));

    pInst->pFld = apr_palloc(pPool, sizeof(CardPlayerA_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_player.pImplicit = pInst;
    pInst->pFld->m_player.Free = Free;

    pInst->pFld->m_player.GetMoney = GetMoney;
    pInst->pFld->m_player.SetMoney = SetMoney;
    pInst->pFld->m_player.ChangeMoney = ChangeMoney;

    pInst->pFld->m_dblMoney = 0;

    return pInst;
}

ICardPlayer * CardPlayerA2ICardPlayer(CardPlayerA * pInst)
{
    return &(pInst->pFld->m_player);
}

void CardPlayerA_Free(CardPlayerA ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
