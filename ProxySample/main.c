
#include <stdio.h>
#include <stdlib.h>
#include <apr_pools.h>
#include "ISearcher.h"
#include "SearcherProxy.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;
	
	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

	ISearcher *pSearcher = SearcherProxy2ISearcher(SearcherProxy_New(pMemPool));
	pSearcher->DoSearch(pSearcher, "杨过", "玉女心经", pMemPool);

	apr_pool_destroy(pMemPool);

	apr_terminate();

	return EXIT_SUCCESS;
}