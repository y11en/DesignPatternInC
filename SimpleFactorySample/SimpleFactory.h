
#include <apr_pools.h>
#include "IChart.h"

#ifndef CHART_TYPE
#define CHART_TYPE

typedef enum ChartType ChartType;

enum ChartType
{
	CHART_NULL = 0,
	CHART_HISTOGRAM = 1,
	CHART_LINE = 2,
	CHART_PIE = 3
};

IChart *GetChart(apr_pool_t *pSupPool, ChartType type);

#endif // !CHART_TYPE
