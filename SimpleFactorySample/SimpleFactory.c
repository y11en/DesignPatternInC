
#include "SimpleFactory.h"
#include "ChartHistogram.h"
#include "ChartLine.h"
#include "ChartPie.h"

IChart * GetChart(apr_pool_t *pSupPool, ChartType type)
{
	switch (type)
	{
	case CHART_NULL:
		return NULL;
	case CHART_HISTOGRAM:
		return ChartHistogram2IChart(ChartHistogram_New(pSupPool));
	case CHART_LINE:
		return ChartLine2IChart(ChartLine_New(pSupPool));
	case CHART_PIE:
		return ChartPie2IChart(ChartPie_New(pSupPool));
	default:
		return NULL;
	}
}
