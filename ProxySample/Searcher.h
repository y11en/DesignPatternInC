
#include <apr_pools.h>
#include "ISearcher.h"


#ifndef SEARCHER_H
#define SEARCHER_H

typedef struct Searcher_Fld Searcher_Fld;
typedef struct Searcher Searcher;

struct Searcher
{
	Searcher_Fld *pFld;

	//继承接口，不需要显示声明公共方法
};

Searcher *Searcher_New(apr_pool_t *pSupPool);
ISearcher *Searcher2ISearcher(Searcher *pInst);
void Searcher_Free(Searcher **ppInst);

#endif // !SEARCHER_H
