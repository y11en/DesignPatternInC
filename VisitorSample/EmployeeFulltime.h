
#include <apr_pools.h>
#include "IEmployee.h"


#ifndef EMPLOYEEFULLTIME_H
#define EMPLOYEEFULLTIME_H

typedef struct EmployeeFulltime_Fld EmployeeFulltime_Fld;
typedef struct EmployeeFulltime EmployeeFulltime;

struct EmployeeFulltime
{
	EmployeeFulltime_Fld *pFld;

	//继承接口IEmployee，
	//但是需求要求可以不通过接口访问，即通过接口实现类也可以访问实例，
	//因此，这里在实现类中增加公共方法
	char *(* GetName)(EmployeeFulltime *pInst, apr_pool_t *pPool);
	void (* SetName)(EmployeeFulltime *pInst, const char *pName);
	double (* GetWeeklyWage)(EmployeeFulltime *pInst);
	void (* SetWeeklyWage)(EmployeeFulltime *pInst, double dblWeeklyWage);
	int (* GetWorkTime)(EmployeeFulltime *pInst);
	void (* SetWorkTime)(EmployeeFulltime *pInst, int nWorkTime);
};

EmployeeFulltime *EmployeeFulltime_New(apr_pool_t *pSupPool, const char *pName, double dblWeeklyWage, int nWorkTime);
IEmployee *EmployeeFulltime2IEmployee(EmployeeFulltime *pInst);
void EmployeeFulltime_Free(EmployeeFulltime **ppInst);

#endif // !EMPLOYEEFULLTIME_H
