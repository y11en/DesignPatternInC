
#include <stdio.h>
#include <apr_strings.h>
#include "IgoChessmanBlack.h"

struct IgoChessmanBlack_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IIgoChessman m_igoChessman;

    char *m_pColor;
};

static void Free(IIgoChessman **ppIgoChessman)
{
    IgoChessmanBlack_Free(&(IgoChessmanBlack *)(*ppIgoChessman)->pImplicit);
    *ppIgoChessman = NULL;
}

static char *GetColor(IIgoChessman *pIgoChessman, apr_pool_t *pPool)
{
    IgoChessmanBlack *pInst = (IgoChessmanBlack *)pIgoChessman->pImplicit;
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pColor);
}

static void Display(IIgoChessman *pIgoChessman, Coordinates *pCoord)
{
    IgoChessmanBlack *pInst = (IgoChessmanBlack *)pIgoChessman->pImplicit;
    printf("棋子颜色：%s，棋子位置：(%d, %d)\n", pInst->pFld->m_pColor, pCoord->GetX(pCoord), pCoord->GetY(pCoord));
}

IgoChessmanBlack * IgoChessmanBlack_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    IgoChessmanBlack *pInst = apr_palloc(pPool, sizeof(IgoChessmanBlack));

    pInst->pFld = apr_palloc(pPool, sizeof(IgoChessmanBlack_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_igoChessman.pImplicit = pInst;
    pInst->pFld->m_igoChessman.Free = Free;

    pInst->pFld->m_igoChessman.GetColor = GetColor;
    pInst->pFld->m_igoChessman.Display = Display;
    pInst->pFld->m_pColor = apr_pstrdup(pInst->pFld->m_pPool, "黑色");

    return pInst;
}

IIgoChessman * IgoChessmanBlack2IIgoChessman(IgoChessmanBlack * pInst)
{
    return &(pInst->pFld->m_igoChessman);
}

void IgoChessmanBlack_Free(IgoChessmanBlack **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
