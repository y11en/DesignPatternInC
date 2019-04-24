
#include <apr_pools.h>
#include "INotifier.h"


#ifndef NOTIFIERALLY_H
#define NOTIFIERALLY_H

typedef struct NotifierAlly_Fld NotifierAlly_Fld;
typedef struct NotifierAlly NotifierAlly;

struct NotifierAlly
{
	NotifierAlly_Fld *pFld;
};

NotifierAlly *NotifierAlly_New(apr_pool_t *pSupPool, const char *pAllyName);
INotifier *NotifierAlly2INotifier(NotifierAlly *pInst);
void NotifierAlly_Free(NotifierAlly **ppInst);

#endif // !NOTIFIERALLY_H
