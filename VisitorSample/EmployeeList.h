
#include <apr_pools.h>
#include "IEmployee.h"
#include "IDepartment.h"


#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

typedef struct EmployeeList_Fld EmployeeList_Fld;
typedef struct EmployeeList EmployeeList;

struct EmployeeList
{
    EmployeeList_Fld *pFld;

    void (* AddEmployee)(EmployeeList *pInst, IEmployee *pEmployee);
    void (* Accept)(EmployeeList *pInst, IDepartment *pDepart);
};

EmployeeList *EmployeeList_New(apr_pool_t *pSupPool);
void EmployeeList_Free(EmployeeList **ppInst);

#endif // !EMPLOYEELIST_H
