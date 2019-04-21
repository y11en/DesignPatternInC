
#include "PlayerA.h"
#include "Mediator.h"

struct PlayerA_Fld
{
    apr_pool_t *m_pPool;

    ICardPlayer m_player;

    double m_dblMoney;
};

static void Free(ICardPlayer **ppCardPlayer)
{
    PlayerA_Free(&(PlayerA *)(*ppCardPlayer)->pImplicit);
    *ppCardPlayer = NULL;
}

static double GetMoney(ICardPlayer *pCardPlayer)
{
    PlayerA *pInst = (PlayerA *)pCardPlayer->pImplicit;
    return pInst->pFld->m_dblMoney;
}

static void SetMoney(ICardPlayer *pCardPlayer, double dblMoney)
{
    PlayerA *pInst = (PlayerA *)pCardPlayer->pImplicit;
    pInst->pFld->m_dblMoney = dblMoney;
}

static void ChangeMoney(ICardPlayer *pCardPlayer, double dblMoney, Mediator *pMediator)
{
    PlayerA *pInst = (PlayerA *)pCardPlayer->pImplicit;
    pMediator->PlayerAWin(pMediator, dblMoney);
}

PlayerA * PlayerA_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    PlayerA *pInst = apr_palloc(pPool, sizeof(PlayerA));

    pInst->pFld = apr_palloc(pPool, sizeof(PlayerA_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_player.pImplicit = pInst;
    pInst->pFld->m_player.Free = Free;

    pInst->pFld->m_player.GetMoney = GetMoney;
    pInst->pFld->m_player.SetMoney = SetMoney;
    pInst->pFld->m_player.ChangeMoney = ChangeMoney;

    pInst->pFld->m_dblMoney = 0;

    return pInst;
}

ICardPlayer * PlayerA2ICardPlayer(PlayerA * pInst)
{
    return &(pInst->pFld->m_player);
}

void PlayerA_Free(PlayerA ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
