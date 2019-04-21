
#include <apr_pools.h>
#include "INotifier.h"


#ifndef ALLYREMINDER_H
#define ALLYREMINDER_H

typedef struct AllyReminder_Fld AllyReminder_Fld;
typedef struct AllyReminder AllyReminder;

struct AllyReminder
{
	AllyReminder_Fld *pFld;
};

AllyReminder *AllyReminder_New(apr_pool_t *pSupPool, const char *pAllyName);
INotifier *AllyReminder2INotifier(AllyReminder *pInst);
void AllyReminder_Free(AllyReminder **ppInst);

#endif // !ALLYREMINDER_H
