
#include "DepartmentFA.h"

struct DepartmentFA_Fld
{
	apr_pool_t *m_pPool;

	IDepartment m_department;
};

static void Free(IDepartment **ppDepart)
{
	DepartmentFA_Free(&(DepartmentFA *)(*ppDepart)->pImplicit);
	*ppDepart = NULL;
}

static void VisitFulltimeEmployee(IDepartment *pDepart, EmployeeFulltime *pFulltimeEmployee)
{
	DepartmentFA *pInst = (DepartmentFA *)pDepart->pImplicit;
	//
}

static void VisitPartTimeEmployee(IDepartment *pDepart, EmployeePartTime *pPartTimeEmployee)
{
	DepartmentFA *pInst = (DepartmentFA *)pDepart->pImplicit;
	//
}

DepartmentFA * DepartmentFA_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	DepartmentFA *pInst = apr_palloc(pPool, sizeof(DepartmentFA));

	pInst->pFld = apr_palloc(pPool, sizeof(DepartmentFA_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_department.pImplicit = pInst;
	pInst->pFld->m_department.Free = Free;

	pInst->pFld->m_department.VisitFulltimeEmployee = VisitFulltimeEmployee;
	pInst->pFld->m_department.VisitPartTimeEmployee = VisitPartTimeEmployee;

	return pInst;
}

IDepartment * DepartmentFA2IDepartment(DepartmentFA * pInst)
{
	return &(pInst->pFld->m_department);
}

void DepartmentFA_Free(DepartmentFA ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
