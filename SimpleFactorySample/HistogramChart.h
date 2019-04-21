
#include <apr_pools.h>
#include "IChart.h"


#ifndef HISTOGRAMCHART_H
#define HISTOGRAMCHART_H

typedef struct HistogramChart_Fld HistogramChart_Fld;
typedef struct HistogramChart HistogramChart;

struct HistogramChart
{
	HistogramChart_Fld *pFld;

	//继承接口，不需要显式声明继承自接口的方法，
	//这样相当于规定
	//如需调用继承自接口的方法，则将该实例转换为接口类型
	//也就只提供了一种接口方法调用方式
};

HistogramChart *const HistogramChart_New(apr_pool_t *pSupPool);
IChart *const HistogramChart2IChart(HistogramChart *pInst);
void HistogramChart_Free(HistogramChart **ppInst);

#endif // !HISTOGRAMCHART_H
