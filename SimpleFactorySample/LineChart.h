
#include <apr_pools.h>
#include "IChart.h"


#ifndef LINECHART_H
#define LINECHART_H

typedef struct LineChart_Fld LineChart_Fld;
typedef struct LineChart LineChart;

struct LineChart
{
	LineChart_Fld *pFld;
};

LineChart *const LineChart_New(apr_pool_t *pSupPool);
IChart *const LineChart2IChart(LineChart *pInst);
void LineChart_Free(LineChart **pInst);

#endif // !LINECHART_H
