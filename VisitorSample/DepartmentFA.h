
#include <apr_pools.h>
#include "IDepartment.h"


#ifndef DEPARTMENTFA_H
#define DEPARTMENTFA_H

typedef struct DepartmentFA_Fld DepartmentFA_Fld;
typedef struct DepartmentFA DepartmentFA;

struct DepartmentFA
{
	DepartmentFA_Fld *pFld;
};

DepartmentFA *DepartmentFA_New(apr_pool_t *pSupPool);
IDepartment *DepartmentFA2IDepartment(DepartmentFA *pInst);
void DepartmentFA_Free(DepartmentFA **ppInst);

#endif // !DEPARTMENTFA_H
