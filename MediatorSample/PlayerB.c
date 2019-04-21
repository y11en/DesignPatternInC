
#include "PlayerB.h"
#include "Mediator.h"

struct PlayerB_Fld
{
    apr_pool_t *m_pPool;

    ICardPlayer m_player;

    double m_dblMoney;
};

static void Free(ICardPlayer **ppCardPlayer)
{
    PlayerB_Free(&(PlayerB *)(*ppCardPlayer)->pImplicit);
    *ppCardPlayer = NULL;
}

static double GetMoney(ICardPlayer *pCardPlayer)
{
    PlayerB *pInst = (PlayerB *)pCardPlayer->pImplicit;
    return pInst->pFld->m_dblMoney;
}

static void SetMoney(ICardPlayer *pCardPlayer, double dblMoney)
{
    PlayerB *pInst = (PlayerB *)pCardPlayer->pImplicit;
    pInst->pFld->m_dblMoney = dblMoney;
}

static void ChangeMoney(ICardPlayer *pCardPlayer, double dblMoney, Mediator *pMediator)
{
    PlayerB *pInst = (PlayerB *)pCardPlayer->pImplicit;
    pMediator->PlayerBWin(pMediator, dblMoney);
}

PlayerB * PlayerB_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    PlayerB *pInst = apr_palloc(pPool, sizeof(PlayerB));

    pInst->pFld = apr_palloc(pPool, sizeof(PlayerB_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_player.pImplicit = pInst;
    pInst->pFld->m_player.Free = Free;

    pInst->pFld->m_player.GetMoney = GetMoney;
    pInst->pFld->m_player.SetMoney = SetMoney;
    pInst->pFld->m_player.ChangeMoney = ChangeMoney;

    pInst->pFld->m_dblMoney = 0;

    return pInst;
}

ICardPlayer * PlayerB2ICardPlayer(PlayerB * pInst)
{
    return &(pInst->pFld->m_player);
}

void PlayerB_Free(PlayerB ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
