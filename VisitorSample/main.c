
#include <stdio.h>
#include <apr_pools.h>
#include "EmployeeList.h"
#include "IEmployee.h"
#include "EmployeeFulltime.h"
#include "EmployeePartTime.h"
#include "IDepartment.h"
#include "DepartmentFA.h"
#include "DepartmentHR.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    EmployeeList *pList = EmployeeList_New(pMemPool);
    IEmployee *pFltm1 = EmployeeFulltime2IEmployee(EmployeeFulltime_New(pMemPool, "ÕÅÎÞ¼É", 3200, 45));
    IEmployee *pFltm2 = EmployeeFulltime2IEmployee(EmployeeFulltime_New(pMemPool, "Ñî¹ý", 2000, 40));
    IEmployee *pFltm3 = EmployeeFulltime2IEmployee(EmployeeFulltime_New(pMemPool, "¶ÎÓþ", 2400, 38));
    IEmployee *pPttm1 = EmployeePartTime2IEmployee(EmployeePartTime_New(pMemPool, "ºéÆß¹«", 80, 20));
    IEmployee *pPttm2 = EmployeePartTime2IEmployee(EmployeePartTime_New(pMemPool, "¹ù¾¸", 60, 18));

    pList->AddEmployee(pList, pFltm1);
    pList->AddEmployee(pList, pFltm2);
    pList->AddEmployee(pList, pFltm3);
    pList->AddEmployee(pList, pPttm1);
    pList->AddEmployee(pList, pPttm2);

    IDepartment *pDepart = DepartmentFA2IDepartment(DepartmentFA_New(pMemPool));
    pList->Accept(pList, pDepart);

    pDepart->Free(&pDepart);
    pFltm1->Free(&pFltm1);
    pFltm2->Free(&pFltm2);
    pFltm3->Free(&pFltm3);
    pPttm1->Free(&pPttm1);
    pPttm2->Free(&pPttm2);
    EmployeeList_Free(&pList);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}