
#include <stdio.h>
#include <apr_strings.h>
#include "Searcher.h"

struct Searcher_Fld
{
	apr_pool_t *m_pPool;

	//继承接口
	ISearcher m_searcher;
};

static void Free(ISearcher **ppSearcher)
{
	Searcher_Free(&(Searcher *)(*ppSearcher)->pImplicit);
	*ppSearcher = NULL;
}

static char *DoSearch(ISearcher *pSearcher, const char *pUserID, const char *pKeyword, apr_pool_t *pPool)
{
	printf("用户\'%s\'使用关键词\'%s\'查询商务信息！\n", pUserID, pKeyword);
	return apr_pstrdup(pPool, "返回具体的内容.");
}

Searcher * Searcher_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Searcher *pInst = apr_palloc(pPool, sizeof(Searcher));

	pInst->pFld = apr_palloc(pPool, sizeof(Searcher_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_searcher.pImplicit = pInst;
	pInst->pFld->m_searcher.Free = Free;
	
	pInst->pFld->m_searcher.DoSearch = DoSearch;

	return pInst;
}

ISearcher * Searcher2ISearcher(Searcher * pInst)
{
	return &(pInst->pFld->m_searcher);
}

void Searcher_Free(Searcher ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
