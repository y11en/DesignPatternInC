
#include <apr_ring_ext.h>
#include "EmployeeList.h"

GENERIC_RING(IEmployee)

struct EmployeeList_Fld
{
    apr_pool_t *m_pPool;

    RING(IEmployee) *m_pEmployees;
};

static void AddEmployee(EmployeeList *pInst, IEmployee *pEmployee)
{
    RING_ELEM(IEmployee) *pElem = apr_palloc(pInst->pFld->m_pPool, sizeof(RING_ELEM(IEmployee)));
    pElem->pInst = pEmployee;
    APR_RING_INSERT_TAIL(pInst->pFld->m_pEmployees, pElem, RING_ELEM(IEmployee), RING_LINK);
}

static void Accept(EmployeeList *pInst, IDepartment *pDepart)
{
    RING_ELEM(IEmployee) *pIterator;
    for (pIterator = APR_RING_FIRST(pInst->pFld->m_pEmployees); pIterator != APR_RING_SENTINEL(pInst->pFld->m_pEmployees, RING_ELEM(IEmployee), RING_LINK); pIterator = APR_RING_NEXT(pIterator, RING_LINK))
    {
        pIterator->pInst->Accept(pIterator->pInst, pDepart);
    }
}

EmployeeList * EmployeeList_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    EmployeeList *pInst = apr_palloc(pPool, sizeof(EmployeeList));
    
    pInst->pFld = apr_palloc(pPool, sizeof(EmployeeList_Fld));
    pInst->pFld->m_pPool = pPool;
    
    pInst->pFld->m_pEmployees = apr_palloc(pInst->pFld->m_pPool, sizeof(RING(IEmployee)));
    APR_RING_INIT(pInst->pFld->m_pEmployees, RING_ELEM(IEmployee), RING_LINK);

    pInst->AddEmployee = AddEmployee;
    pInst->Accept = Accept;

    return pInst;
}

void EmployeeList_Free(EmployeeList ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
