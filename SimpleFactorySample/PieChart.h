
#include <apr_pools.h>
#include "IChart.h"


#ifndef PIECHART_H
#define PIECHART_H

typedef struct PieChart_Fld PieChart_Fld;
typedef struct PieChart PieChart;

struct PieChart
{
	PieChart_Fld *pFld;
};

PieChart *const PieChart_New(apr_pool_t *pSupPool);
IChart *const PieChart2IChart(PieChart *pInst);
void PieChart_Free(PieChart **ppInst);

#endif // !PIECHART_H
