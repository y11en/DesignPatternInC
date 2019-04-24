
#include <apr_pools.h>
#include "IChart.h"


#ifndef CHARTPIE_H
#define CHARTPIE_H

typedef struct ChartPie_Fld ChartPie_Fld;
typedef struct ChartPie ChartPie;

struct ChartPie
{
	ChartPie_Fld *pFld;
};

ChartPie *ChartPie_New(apr_pool_t *pSupPool);
IChart *ChartPie2IChart(ChartPie *pInst);
void ChartPie_Free(ChartPie **ppInst);

#endif // !CHARTPIE_H
