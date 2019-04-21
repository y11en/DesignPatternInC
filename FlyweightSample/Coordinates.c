
#include "Coordinates.h"


struct Coordinates_Fld
{
    apr_pool_t *m_pPool;

    int m_X;
    int m_Y;
};

int GetX(Coordinates *pInst)
{
    return pInst->pFld->m_X;
}

void SetX(Coordinates *pInst, int x)
{
    pInst->pFld->m_X = x;
}

int GetY(Coordinates *pInst)
{
    return pInst->pFld->m_Y;
}

void SetY(Coordinates *pInst, int y)
{
    pInst->pFld->m_Y = y;
}

Coordinates * Coordinates_New(apr_pool_t * pSupPool, int x, int y)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Coordinates *pInst = apr_palloc(pPool, sizeof(Coordinates));

    pInst->pFld = apr_palloc(pPool, sizeof(Coordinates_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_X = x;
    pInst->pFld->m_Y = y;

    pInst->GetX = GetX;
    pInst->SetX = SetX;
    pInst->GetY = GetY;
    pInst->SetY = SetY;

    return pInst;
}

void Coordinates_Free(Coordinates ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
