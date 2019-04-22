
#include <apr_pools.h>
#include "IDepartment.h"


#ifndef DEPARTMENTHR_H
#define DEPARTMENTHR_H

typedef struct DepartmentHR_Fld DepartmentHR_Fld;
typedef struct DepartmentHR DepartmentHR;

struct DepartmentHR
{
    DepartmentHR_Fld *pFld;
};

DepartmentHR *DepartmentHR_New(apr_pool_t *pSupPool);
IDepartment *DepartmentHR2IDepartment(DepartmentHR *pInst);
void DepartmentHR_Free(DepartmentHR **ppInst);

#endif // !DEPARTMENTHR_H
