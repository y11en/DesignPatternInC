
#include <apr_pools.h>

#ifndef ISEARCHER_H
#define ISEARCHER_H

typedef struct ISearcher ISearcher;

struct ISearcher
{
	void *pImplicit;

	char *(* DoSearch)(ISearcher *pSearcher, const char *pUserID, const char *pKeyword, apr_pool_t *pPool);

	void (* Free)(ISearcher **ppSearcher);
};

#endif // !ISEARCHER_H
