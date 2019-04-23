
#include <apr_strings.h>
#include "EmployeePartTime.h"
#include "IDepartment.h"

struct EmployeePartTime_Fld
{
	apr_pool_t *m_pPool;

	IEmployee m_employee;

	char *m_pName;
	double m_dblHourWage;
	int m_nWorkTime;
};

static void Free(IEmployee **ppEmployee)
{
	EmployeePartTime_Free(&(EmployeePartTime *)(*ppEmployee)->pImplicit);
	*ppEmployee = NULL;
}

static void Accept(IEmployee *pEmployee, IDepartment *pDepart)
{
	EmployeePartTime *pInst = (EmployeePartTime *)pEmployee->pImplicit;
	
    pDepart->VisitPartTimeEmployee(pDepart, pInst);
}

static char *GetName(EmployeePartTime *pInst, apr_pool_t *pPool)
{
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetName(EmployeePartTime *pInst, const char *pName)
{
	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
}

static double GetHourWage(EmployeePartTime *pInst)
{
	return pInst->pFld->m_dblHourWage;
}

static void SetHourWage(EmployeePartTime *pInst, double dblHourWage)
{
	pInst->pFld->m_dblHourWage = dblHourWage;
}

static int GetWorkTime(EmployeePartTime *pInst)
{
	return pInst->pFld->m_nWorkTime;
}

static void SetWorkTime(EmployeePartTime *pInst, int nWorkTime)
{
	pInst->pFld->m_nWorkTime = nWorkTime;
}

EmployeePartTime * EmployeePartTime_New(apr_pool_t * pSupPool, const char * pName, double dblHourWage, int nWorkTime)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    EmployeePartTime *pInst = apr_palloc(pPool, sizeof(EmployeePartTime));

    pInst->pFld = apr_palloc(pPool, sizeof(EmployeePartTime_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_employee.pImplicit = pInst;
    pInst->pFld->m_employee.Free = Free;

    pInst->pFld->m_employee.Accept = Accept;

    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
    pInst->pFld->m_dblHourWage = dblHourWage;
    pInst->pFld->m_nWorkTime = nWorkTime;

    pInst->GetName = GetName;
    pInst->SetName = SetName;
    pInst->GetHourWage = GetHourWage;
    pInst->SetHourWage = SetHourWage;
    pInst->GetWorkTime = GetWorkTime;
    pInst->SetWorkTime = SetWorkTime;

    return pInst;
}

IEmployee * EmployeePartTime2IEmployee(EmployeePartTime * pInst)
{
	return &(pInst->pFld->m_employee);
}

void EmployeePartTime_Free(EmployeePartTime ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
