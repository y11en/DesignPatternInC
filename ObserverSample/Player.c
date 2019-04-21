
#include <stdio.h>
#include <apr_strings.h>
#include "INotifier.h"
#include "Player.h"

struct Player_Fld
{
	apr_pool_t *m_pPool;

	IObserver m_observer;

	char *m_pName;
};

static void Free(IObserver **ppObserver)
{
	Player_Free(&(Player *)(*ppObserver)->pImplicit);
	*ppObserver = NULL;
}

static char *GetName(IObserver *pObserver, apr_pool_t *pPool)
{
	Player *pInst = (Player *)pObserver->pImplicit;
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetName(IObserver *pObserver, const char *pName)
{
	Player *pInst = (Player *)pObserver->pImplicit;
	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
}

static void Help(IObserver *pObserver)
{
	Player *pInst = (Player *)pObserver->pImplicit;
	printf("坚持住，%s来就你啦~~\n", pInst->pFld->m_pName);
}

static void BeAttacked(IObserver *pObserver, INotifier *pNotifier)
{
	Player *pInst = (Player *)pObserver->pImplicit;
	printf("%s被攻击。\n", pInst->pFld->m_pName);
	pNotifier->Notify(pNotifier, pInst->pFld->m_pName);
}

Player * Player_New(apr_pool_t * pSupPool, const char * pName)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Player *pInst = apr_palloc(pPool, sizeof(Player));

	pInst->pFld = apr_palloc(pPool, sizeof(Player_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_observer.pImplicit = pInst;
	pInst->pFld->m_observer.Free = Free;

	pInst->pFld->m_observer.GetName = GetName;
	pInst->pFld->m_observer.SetName = SetName;
	pInst->pFld->m_observer.Help = Help;
	pInst->pFld->m_observer.BeAttacked = BeAttacked;

	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);

	return pInst;
}

IObserver * Player2IObserver(Player * pInst)
{
	return &(pInst->pFld->m_observer);
}

void Player_Free(Player ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
