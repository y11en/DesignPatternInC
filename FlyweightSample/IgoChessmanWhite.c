
#include <stdio.h>
#include <apr_strings.h>
#include "IgoChessmanWhite.h"

struct IgoChessmanWhite_Fld
{
    apr_pool_t *m_pPool;

    IIgoChessman m_igoChessman;

    char *m_pColor;
};

static void Free(IIgoChessman **ppIgoChessman)
{
    IgoChessmanWhite_Free(&(IgoChessmanWhite *)(*ppIgoChessman)->pImplicit);
    *ppIgoChessman = NULL;
}

static char *GetColor(IIgoChessman *pIgoChessman, apr_pool_t *pPool)
{
    IgoChessmanWhite *pInst = (IgoChessmanWhite *)pIgoChessman->pImplicit;
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pColor);
}

static void Display(IIgoChessman *pIgoChessman, Coordinates *pCoord)
{
    IgoChessmanWhite *pInst = (IgoChessmanWhite *)pIgoChessman->pImplicit;
    printf("棋子颜色：%s，棋子位置：(%d, %d)\n", pInst->pFld->m_pColor, pCoord->GetX(pCoord), pCoord->GetY(pCoord));
}

IgoChessmanWhite * IgoChessmanWhite_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    IgoChessmanWhite *pInst = apr_palloc(pPool, sizeof(IgoChessmanWhite));

    pInst->pFld = apr_palloc(pPool, sizeof(IgoChessmanWhite_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_igoChessman.pImplicit = pInst;
    pInst->pFld->m_igoChessman.Free = Free;

    pInst->pFld->m_igoChessman.GetColor = GetColor;
    pInst->pFld->m_igoChessman.Display = Display;
    pInst->pFld->m_pColor = apr_pstrdup(pInst->pFld->m_pPool, "白色");

    return pInst;
}

IIgoChessman * IgoChessmanWhite2IIgoChessman(IgoChessmanWhite * pInst)
{
    return &(pInst->pFld->m_igoChessman);
}

void IgoChessmanWhite_Free(IgoChessmanWhite ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
