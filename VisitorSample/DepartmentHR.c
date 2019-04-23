
#include <stdio.h>
#include "DepartmentHR.h"
#include "EmployeeFulltime.h"
#include "EmployeePartTime.h"

struct DepartmentHR_Fld
{
    apr_pool_t *m_pPool;

    IDepartment m_department;
};

static void Free(IDepartment **ppDepart)
{
    DepartmentHR_Free(&(DepartmentHR *)(*ppDepart)->pImplicit);
    *ppDepart = NULL;
}

static void VisitFulltimeEmployee(IDepartment *pDepart, EmployeeFulltime *pFulltimeEmployee)
{
    DepartmentHR *pInst = (DepartmentHR *)pDepart->pImplicit;

    int nWorkTime = pFulltimeEmployee->GetWorkTime(pFulltimeEmployee);
    char *pName = pFulltimeEmployee->GetName(pFulltimeEmployee, pInst->pFld->m_pPool);
    printf("正式员工%s实际工作时间为：%d小时.\n", pName, nWorkTime);
    if (nWorkTime > 40)
    {
        printf("正式员工%s加班时间为：%d小时。\n", pName, nWorkTime - 40);
    }
    else if (nWorkTime < 40)
    {
        printf("正式员工%s请假时间为：%d小时。\n", pName, 40 - nWorkTime);
    }
}

static void VisitPartTimeEmployee(IDepartment *pDepart, EmployeePartTime *pPartTimeEmployee)
{
    DepartmentHR *pInst = (DepartmentHR *)pDepart->pImplicit;

    int nWorkTime = pPartTimeEmployee->GetWorkTime(pPartTimeEmployee);
    char *pName = pPartTimeEmployee->GetName(pPartTimeEmployee, pInst->pFld->m_pPool);
    printf("临时员工%s实际工作时间为：%d小时。\n", pName, nWorkTime);
}

DepartmentHR * DepartmentHR_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DepartmentHR *pInst = apr_palloc(pPool, sizeof(DepartmentHR));

    pInst->pFld = apr_palloc(pPool, sizeof(DepartmentHR_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_department.pImplicit = pInst;
    pInst->pFld->m_department.Free = Free;

    pInst->pFld->m_department.VisitFulltimeEmployee = VisitFulltimeEmployee;
    pInst->pFld->m_department.VisitPartTimeEmployee = VisitPartTimeEmployee;

    return pInst;
}

IDepartment * DepartmentHR2IDepartment(DepartmentHR * pInst)
{
    return &(pInst->pFld->m_department);
}

void DepartmentHR_Free(DepartmentHR ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
