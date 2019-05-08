
#include <malloc.h>
#include <stdio.h>
#include <apr_strings.h>
#include <apr_ring_ext.h>
#include "NotifierAlly.h"
#include "IObserver.h"

//实例化泛型环
GENERIC_RING(IObserver)

struct NotifierAlly_Fld
{
	apr_pool_t *m_pPool;

	INotifier m_notifier;

	char *m_pName;

	RING(IObserver) *m_pObservers;
};

static void Free(INotifier **ppNotifier)
{
	NotifierAlly_Free(&(NotifierAlly *)(*ppNotifier)->pImplicit);
	*ppNotifier = NULL;
}

static char *GetAllyName(INotifier *pNotifier, apr_pool_t *pPool)
{
	NotifierAlly *pInst = (NotifierAlly *)pNotifier->pImplicit;
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetAllyName(INotifier *pNotifier, const char *pName)
{
	NotifierAlly *pInst = (NotifierAlly *)pNotifier->pImplicit;
	free(pInst->pFld->m_pName);
	pInst->pFld->m_pName = memcpy(malloc(strlen(pName) + 1), pName, strlen(pName) + 1);
}

static void Join(INotifier *pNotifier, IObserver *pObserver)
{
	NotifierAlly *pInst = (NotifierAlly *)pNotifier->pImplicit;
	RING_ELEM(IObserver) *pElem = apr_palloc(pInst->pFld->m_pPool, sizeof(RING_ELEM(IObserver)));
	pElem->pInst = pObserver;
	APR_RING_INSERT_TAIL(pInst->pFld->m_pObservers, pElem, RING_ELEM(IObserver), RING_LINK);

	printf("%s加入%s战队。\n", pObserver->GetName(pObserver, pInst->pFld->m_pPool), pInst->pFld->m_pName);
}

static void Quit(INotifier *pNotifier, IObserver *pObserver)
{
	NotifierAlly *pInst = (NotifierAlly *)pNotifier->pImplicit;

	RING_ELEM(IObserver) *pIterator;
	for (pIterator = APR_RING_FIRST(pInst->pFld->m_pObservers); pIterator != APR_RING_SENTINEL(pInst->pFld->m_pObservers, RING_ELEM(IObserver), RING_LINK); pIterator = APR_RING_NEXT(pIterator, RING_LINK))
	{
		if (pIterator->pInst == pObserver)
		{
			APR_RING_REMOVE(pIterator, RING_LINK);
			break;
		}
	}

	printf("%s退出%s战队.\n", pObserver->GetName(pObserver, pInst->pFld->m_pPool), pInst->pFld->m_pName);
}

static void Notify(INotifier *pNotifier, const char *pName)
{
	NotifierAlly *pInst = (NotifierAlly *)pNotifier->pImplicit;
	printf("%s战队紧急通知，盟友%s正遭受敌人攻击！\n", pInst->pFld->m_pName, pName);

	RING_ELEM(IObserver) *pIterator;
	for (pIterator = APR_RING_FIRST(pInst->pFld->m_pObservers); pIterator != APR_RING_SENTINEL(pInst->pFld->m_pObservers, RING_ELEM(IObserver), RING_LINK); pIterator = APR_RING_NEXT(pIterator, RING_LINK))
	{
		if (strcmp((const char *)pIterator->pInst->GetName(pIterator->pInst, pInst->pFld->m_pPool), pName))
		{
			pIterator->pInst->Help(pIterator->pInst);
		}
	}
}

NotifierAlly * NotifierAlly_New(apr_pool_t * pSupPool, const char * pAllyName)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	NotifierAlly *pInst = apr_palloc(pPool, sizeof(NotifierAlly));

	pInst->pFld = apr_palloc(pPool, sizeof(NotifierAlly_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_notifier.pImplicit = pInst;
	pInst->pFld->m_notifier.Free = Free;

	pInst->pFld->m_notifier.GetAllyName = GetAllyName;
	pInst->pFld->m_notifier.SetAllyName = SetAllyName;
	pInst->pFld->m_notifier.Join = Join;
	pInst->pFld->m_notifier.Quit = Quit;
	pInst->pFld->m_notifier.Notify = Notify;

	pInst->pFld->m_pName = memcpy(malloc(strlen(pAllyName) + 1), pAllyName, strlen(pAllyName) + 1);
	pInst->pFld->m_pObservers = apr_palloc(pInst->pFld->m_pPool, sizeof(RING(IObserver)));
	APR_RING_INIT(pInst->pFld->m_pObservers, RING_ELEM(IObserver), RING_LINK);

	return pInst;
}

INotifier * NotifierAlly2INotifier(NotifierAlly * pInst)
{
	return &(pInst->pFld->m_notifier);
}

void NotifierAlly_Free(NotifierAlly ** ppInst)
{
	free((*ppInst)->pFld->m_pName);
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
