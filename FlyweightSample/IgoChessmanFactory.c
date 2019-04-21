
#include <apr_hash.h>
#include <apr_strings.h>
#include "IgoChessmanFactory.h"
#include "IgoChessmanBlack.h"
#include "IgoChessmanWhite.h"

//µ¥Àý
static IgoChessmanFactory *pSingleton = NULL;

struct IgoChessmanFactory_Fld
{
    apr_pool_t *m_pPool;

    //ÏíÔª³Ø
    apr_hash_t *m_pHashTab;
};

IIgoChessman *GetIgoChessman(IgoChessmanFactory *pInst, ColorType color)
{
    return apr_hash_get(pInst->pFld->m_pHashTab, (color == COLOR_WHITE ? "WHITE" : "BLACK"), APR_HASH_KEY_STRING);
}

static IgoChessmanFactory * IgoChessmanFactory_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    IgoChessmanFactory *pInst = apr_palloc(pPool, sizeof(IgoChessmanFactory));

    pInst->pFld = apr_palloc(pPool, sizeof(IgoChessmanFactory_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_pHashTab = apr_hash_make(pInst->pFld->m_pPool);

    IIgoChessman *white = IgoChessmanWhite2IIgoChessman(IgoChessmanWhite_New(pInst->pFld->m_pPool));
    IIgoChessman *black = IgoChessmanBlack2IIgoChessman(IgoChessmanBlack_New(pInst->pFld->m_pPool));
    apr_hash_set(pInst->pFld->m_pHashTab, apr_pstrdup(pInst->pFld->m_pPool, "WHITE"), APR_HASH_KEY_STRING, white);
    apr_hash_set(pInst->pFld->m_pHashTab, apr_pstrdup(pInst->pFld->m_pPool, "BLACK"), APR_HASH_KEY_STRING, black);

    pInst->GetIgoChessman = GetIgoChessman;

    return pInst;
}

IgoChessmanFactory * GetIgoChessmanFactoryInstance(apr_pool_t * pSupPool)
{
    return pSingleton == NULL ? pSingleton = IgoChessmanFactory_New(pSupPool) : pSingleton;
}

void IgoChessmanFactory_Free(IgoChessmanFactory ** ppInst)
{
    IIgoChessman *white = apr_hash_get((*ppInst)->pFld->m_pHashTab, "WHITE", APR_HASH_KEY_STRING);
    white->Free(&white);
    IIgoChessman *black = apr_hash_get((*ppInst)->pFld->m_pHashTab, "BLACK", APR_HASH_KEY_STRING);
    black->Free(&black);

    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;

    pSingleton = NULL;
}
