
#include <apr_strings.h>
#include "EmployeePartTime.h"

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
	//
}

static char *GetName(EmployeePartTime *pInst, apr_pool_t *pPool)
{
	return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pPool);
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
	return NULL;
}

IEmployee * EmployeePartTime2IEmployee(EmployeePartTime * pInst)
{
	return NULL;
}

void EmployeePartTime_Free(EmployeePartTime ** ppInst)
{
}
