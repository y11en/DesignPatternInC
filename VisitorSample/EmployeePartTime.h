
#include <apr_pools.h>
#include "IEmployee.h"


#ifndef EMPLOYEEPARTTIME_H
#define EMPLOYEEPARTTIME_H

typedef struct EmployeePartTime_Fld EmployeePartTime_Fld;
typedef struct EmployeePartTime EmployeePartTime;

struct EmployeePartTime
{
	EmployeePartTime_Fld *pFld;

	//继承接口IEmployee，
	//但是需求要求可以通过接口实现类访问实例，
	//因此这里添加公共方法
	char *(* GetName)(EmployeePartTime *pInst, apr_pool_t *pPool);
	void (* SetName)(EmployeePartTime *pInst, const char *pName);
	double (* GetHourWage)(EmployeePartTime *pInst);
	void (* SetHourWage)(EmployeePartTime *pInst, double dblHourWage);
	int (* GetWorkTime)(EmployeePartTime *pInst);
	void (* SetWorkTime)(EmployeePartTime *pInst, int nWorkTime);
};

EmployeePartTime *EmployeePartTime_New(apr_pool_t *pSupPool, const char *pName, double dblHourWage, int nWorkTime);
IEmployee *EmployeePartTime2IEmployee(EmployeePartTime *pInst);
void EmployeePartTime_Free(EmployeePartTime **ppInst);

#endif // !EMPLOYEEPARTTIME_H
