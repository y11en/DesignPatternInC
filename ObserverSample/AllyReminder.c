
#include <stdio.h>
#include <apr_strings.h>
#include "apr_ring_ext.h"
#include "IObserver.h"
#include "AllyReminder.h"

//实例化泛型环
GENERIC_RING(IObserver)

struct AllyReminder_Fld
{
	apr_pool_t *m_pPool;

	INotifier m_notifier;

	char *m_pName;

	RING(IObserver) *m_pObservers;
};

static void Free(INotifier **ppNotifier)
{
	AllyReminder_Free(&(AllyReminder *)(*ppNotifier)->pImplicit);
	*ppNotifier = NULL;
}

static char *GetAllyName(INotifier *pNotifier, apr_pool_t *pPool)
{
	AllyReminder *pInst = (AllyReminder *)pNotifier->pImplicit;
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetAllyName(INotifier *pNotifier, const char *pName)
{
	AllyReminder *pInst = (AllyReminder *)pNotifier->pImplicit;
	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
}

static void Join(INotifier *pNotifier, IObserver *pObserver)
{
	AllyReminder *pInst = (AllyReminder *)pNotifier->pImplicit;
	RING_ELEM(IObserver) *pElem = apr_palloc(pInst->pFld->m_pPool, sizeof(RING_ELEM(IObserver)));
	pElem->pInst = pObserver;
	APR_RING_INSERT_TAIL(pInst->pFld->m_pObservers, pElem, RING_ELEM(IObserver), RING_LINK);

	printf("%s加入%s战队。\n", pObserver->GetName(pObserver, pInst->pFld->m_pPool), pInst->pFld->m_pName);
}

static void Quit(INotifier *pNotifier, IObserver *pObserver)
{
	AllyReminder *pInst = (AllyReminder *)pNotifier->pImplicit;

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
	AllyReminder *pInst = (AllyReminder *)pNotifier->pImplicit;
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

AllyReminder * AllyReminder_New(apr_pool_t * pSupPool, const char * pAllyName)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	AllyReminder *pInst = apr_palloc(pPool, sizeof(AllyReminder));

	pInst->pFld = apr_palloc(pPool, sizeof(AllyReminder_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_notifier.pImplicit = pInst;
	pInst->pFld->m_notifier.Free = Free;

	pInst->pFld->m_notifier.GetAllyName = GetAllyName;
	pInst->pFld->m_notifier.SetAllyName = SetAllyName;
	pInst->pFld->m_notifier.Join = Join;
	pInst->pFld->m_notifier.Quit = Quit;
	pInst->pFld->m_notifier.Notify = Notify;

	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pAllyName);
	pInst->pFld->m_pObservers = apr_palloc(pInst->pFld->m_pPool, sizeof(RING(IObserver)));
	APR_RING_INIT(pInst->pFld->m_pObservers, RING_ELEM(IObserver), RING_LINK);

	return pInst;
}

INotifier * AllyReminder2INotifier(AllyReminder * pInst)
{
	return &(pInst->pFld->m_notifier);
}

void AllyReminder_Free(AllyReminder ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
