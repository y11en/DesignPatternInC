
#include <apr_pools.h>
#include "ISearcher.h"


#ifndef SEARCHERPROXY_H
#define SEARCHERPROXY_H

typedef struct SearcherProxy_Fld SearcherProxy_Fld;
typedef struct SearcherProxy SearcherProxy;

struct SearcherProxy
{
	SearcherProxy_Fld *pFld;

	//¼Ì³Ð½Ó¿Ú
};

SearcherProxy *SearcherProxy_New(apr_pool_t *pSupPool);
ISearcher *SearcherProxy2ISearcher(SearcherProxy *pInst);
void SearcherProxy_Free(SearcherProxy **ppInst);

#endif // !SEARCHERPROXY_H
