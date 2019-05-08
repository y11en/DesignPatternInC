
#include <malloc.h>
#include <apr_strings.h>
#include "Chessman.h"

struct Chessman_Fld
{
    apr_pool_t *m_pPool;
    
    char *m_pLabel;
    int m_nX;
    int m_nY;
};

static char *GetLabel(Chessman *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pLabel);
}

static void SetLabel(Chessman *pInst, const char *pLabel)
{
	free(pInst->pFld->m_pLabel);
	pInst->pFld->m_pLabel = memcpy(malloc(strlen(pLabel) + 1), pLabel, strlen(pLabel) + 1);
}

static int GetX(Chessman *pInst)
{
    return pInst->pFld->m_nX;
}

static void SetX(Chessman *pInst, int nX)
{
    pInst->pFld->m_nX = nX;
}

static int GetY(Chessman *pInst)
{
    return pInst->pFld->m_nY;
}

static void SetY(Chessman *pInst, int nY)
{
    pInst->pFld->m_nY = nY;
}

//static Memento *Save(Chessman *pInst, apr_pool_t *pPool)
//{
//    return Memento_New(pPool, apr_pstrdup(pPool, (const char *)pInst->pFld->m_pLabel), pInst->pFld->m_nX, pInst->pFld->m_nY);
//}

static Memento *Save(Chessman *pInst, apr_pool_t *pPool, Memento *pOut)
{
    pOut->SetLabel(pOut, (const char *)apr_pstrdup(pPool, pInst->pFld->m_pLabel));
    pOut->SetX(pOut, pInst->pFld->m_nX);
    pOut->SetY(pOut, pInst->pFld->m_nY);

    return pOut;
}

static void Restore(Chessman *pInst, Memento *pMememto)
{
	free(pInst->pFld->m_pLabel);
	{
		////这里有点瑕疵，频繁调用该函数Restore会导致 一直在pInst->pFld->m_pPool中分配内存 以存储从pMememto读取到的Label。
		//const char *pStr = pMememto->GetLabel(pMememto, pInst->pFld->m_pPool);
		//pInst->pFld->m_pLabel = memcpy(malloc(strlen(pStr) + 1), pStr, strlen(pStr) + 1);

		const char *pStr;
		apr_pool_t *pTmpPool;
		apr_pool_create(&pTmpPool, pInst->pFld->m_pPool);
		pInst->pFld->m_pLabel = (pStr = pMememto->GetLabel(pMememto, pTmpPool), memcpy(malloc(strlen(pStr) + 1), pStr, strlen(pStr) + 1));
		apr_pool_destroy(pTmpPool);
	}
    pInst->pFld->m_nX = pMememto->GetX(pMememto);
    pInst->pFld->m_nY = pMememto->GetY(pMememto);
}

Chessman * Chessman_New(apr_pool_t * pSupPool, const char * pLabel, int nX, int nY)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Chessman *pInst = apr_palloc(pPool, sizeof(Chessman));

    pInst->pFld = apr_palloc(pPool, sizeof(Chessman_Fld));
    pInst->pFld->m_pPool = pPool;

	pInst->pFld->m_pLabel = memcpy(malloc(strlen(pLabel) + 1), pLabel, strlen(pLabel) + 1);
    pInst->pFld->m_nX = nX;
    pInst->pFld->m_nY = nY;

    pInst->GetLabel = GetLabel;
    pInst->SetLabel = SetLabel;
    pInst->GetX = GetX;
    pInst->SetX = SetX;
    pInst->GetY = GetY;
    pInst->SetY = SetY;
    pInst->Save = Save;
    pInst->Restore = Restore;

    return pInst;
}

void Chessman_Free(Chessman **ppInst)
{
	free((*ppInst)->pFld->m_pLabel);
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
