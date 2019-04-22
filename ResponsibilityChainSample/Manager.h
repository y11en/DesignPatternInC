
#include <apr_pools.h>
#include "IApprover.h"


#ifndef MANAGER_H
#define MANAGER_H

typedef struct Manager_Fld Manager_Fld;
typedef struct Manager Manager;

struct Manager
{
    Manager_Fld *pFld;
};

Manager *Manager_New(apr_pool_t *pSupPool, const char *pName);
IApprover *Manager2IApprover(Manager *pInst);
void Manager_Free(Manager **ppInst);

#endif // !MANAGER_H
