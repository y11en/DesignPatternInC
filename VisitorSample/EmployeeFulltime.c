
#include <apr_strings.h>
#include "EmployeeFulltime.h"
#include "IDepartment.h"

struct EmployeeFulltime_Fld
{
	apr_pool_t *m_pPool;

	IEmployee m_employee;

	char *m_pName;
	double m_dblWeeklyWage;
	int m_nWorkTime;
};

static void Free(IEmployee **ppEmployee)
{
	EmployeeFulltime_Free(&(EmployeeFulltime *)(*ppEmployee)->pImplicit);
	*ppEmployee = NULL;
}

static void Accept(IEmployee *pEmployee, IDepartment *pDepart)
{
	EmployeeFulltime *pInst = (EmployeeFulltime *)pEmployee->pImplicit;
	
    pDepart->VisitFulltimeEmployee(pDepart, pInst);
}

static char *GetName(EmployeeFulltime *pInst, apr_pool_t *pPool)
{
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pName);
}

static void SetName(EmployeeFulltime *pInst, const char *pName)
{
	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
}

static double GetWeeklyWage(EmployeeFulltime *pInst)
{
	return pInst->pFld->m_dblWeeklyWage;
}

static void SetWeeklyWage(EmployeeFulltime *pInst, double dblWeeklyWage)
{
	pInst->pFld->m_dblWeeklyWage = dblWeeklyWage;
}

static int GetWorkTime(EmployeeFulltime *pInst)
{
	return pInst->pFld->m_nWorkTime;
}

static void SetWorkTime(EmployeeFulltime *pInst, int nWorkTime)
{
	pInst->pFld->m_nWorkTime = nWorkTime;
}

EmployeeFulltime * EmployeeFulltime_New(apr_pool_t * pSupPool, const char * pName, double dblWeeklyWage, int nWorkTime)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	EmployeeFulltime *pInst = apr_palloc(pPool, sizeof(EmployeeFulltime));

	pInst->pFld = apr_palloc(pPool, sizeof(EmployeeFulltime_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_employee.pImplicit = pInst;
	pInst->pFld->m_employee.Free = Free;

	pInst->pFld->m_employee.Accept = Accept;

	pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
	pInst->pFld->m_dblWeeklyWage = dblWeeklyWage;
	pInst->pFld->m_nWorkTime = nWorkTime;

	pInst->GetName = GetName;
	pInst->SetName = SetName;
	pInst->GetWeeklyWage = GetWeeklyWage;
	pInst->SetWeeklyWage = SetWeeklyWage;
	pInst->GetWorkTime = GetWorkTime;
	pInst->SetWorkTime = SetWorkTime;

	return pInst;
}

IEmployee * EmployeeFulltime2IEmployee(EmployeeFulltime * pInst)
{
	return &(pInst->pFld->m_employee);
}

void EmployeeFulltime_Free(EmployeeFulltime ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
