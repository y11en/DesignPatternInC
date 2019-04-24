
#include <apr_pools.h>
#include "IChart.h"


#ifndef CHARTLINE_H
#define CHARTLINE_H

typedef struct ChartLine_Fld ChartLine_Fld;
typedef struct ChartLine ChartLine;

struct ChartLine
{
	ChartLine_Fld *pFld;
};

ChartLine *ChartLine_New(apr_pool_t *pSupPool);
IChart *ChartLine2IChart(ChartLine *pInst);
void ChartLine_Free(ChartLine **pInst);

#endif // !CHARTLINE_H
