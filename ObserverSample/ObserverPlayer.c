
#include <malloc.h>
#include <stdio.h>
#include <apr_strings.h>
#include "ObserverPlayer.h"
#include "INotifier.h"

struct ObserverPlayer_Fld
{
	apr_pool_t *m_pPool;

	IObserver m_observer;

	char *m_pName;
};

static void Free(IObserver **ppObserver)
{
	ObserverPlayer_Free(&(ObserverPlayer *)(*ppObserver)->pImplicit);
	*ppObserver = NULL;
}

static char *GetName(IObserver *pObserver, apr_pool_t *pPool)
{
	ObserverPlayer *pInst = (ObserverPlayer *)pObserver->pImplicit;
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetName(IObserver *pObserver, const char *pName)
{
	ObserverPlayer *pInst = (ObserverPlayer *)pObserver->pImplicit;
	free(pInst->pFld->m_pName);
	pInst->pFld->m_pName = memcpy(malloc(strlen(pName) + 1), pName, strlen(pName) + 1);
}

static void Help(IObserver *pObserver)
{
	ObserverPlayer *pInst = (ObserverPlayer *)pObserver->pImplicit;
	printf("坚持住，%s来就你啦~~\n", pInst->pFld->m_pName);
}

static void BeAttacked(IObserver *pObserver, INotifier *pNotifier)
{
	ObserverPlayer *pInst = (ObserverPlayer *)pObserver->pImplicit;
	printf("%s被攻击。\n", pInst->pFld->m_pName);
	pNotifier->Notify(pNotifier, pInst->pFld->m_pName);
}

ObserverPlayer * ObserverPlayer_New(apr_pool_t * pSupPool, const char * pName)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	ObserverPlayer *pInst = apr_palloc(pPool, sizeof(ObserverPlayer));

	pInst->pFld = apr_palloc(pPool, sizeof(ObserverPlayer_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_observer.pImplicit = pInst;
	pInst->pFld->m_observer.Free = Free;

	pInst->pFld->m_observer.GetName = GetName;
	pInst->pFld->m_observer.SetName = SetName;
	pInst->pFld->m_observer.Help = Help;
	pInst->pFld->m_observer.BeAttacked = BeAttacked;

	pInst->pFld->m_pName = memcpy(malloc(strlen(pName) + 1), pName, strlen(pName) + 1);

	return pInst;
}

IObserver * ObserverPlayer2IObserver(ObserverPlayer * pInst)
{
	return &(pInst->pFld->m_observer);
}

void ObserverPlayer_Free(ObserverPlayer ** ppInst)
{
	free((*ppInst)->pFld->m_pName);
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
