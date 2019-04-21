
#include "SimpleFactory.h"
#include "HistogramChart.h"
#include "LineChart.h"
#include "PieChart.h"

IChart * GetChart(apr_pool_t *pSupPool, ChartType type)
{
	switch (type)
	{
	case CHART_NULL:
		return NULL;
	case CHART_HISTOGRAM:
		return HistogramChart2IChart(HistogramChart_New(pSupPool));
	case CHART_LINE:
		return LineChart2IChart(LineChart_New(pSupPool));
	case CHART_PIE:
		return PieChart2IChart(PieChart_New(pSupPool));
	default:
		return NULL;
	}
}
