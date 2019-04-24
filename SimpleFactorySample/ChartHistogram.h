
#include <apr_pools.h>
#include "IChart.h"


#ifndef CHARTHISTOGRAM_H
#define CHARTHISTOGRAM_H

typedef struct ChartHistogram_Fld ChartHistogram_Fld;
typedef struct ChartHistogram ChartHistogram;

struct ChartHistogram
{
	ChartHistogram_Fld *pFld;

	//继承接口，不需要显式声明继承自接口的方法，
	//这样相当于规定
	//如需调用继承自接口的方法，则将该实例转换为接口类型
	//也就只提供了一种接口方法调用方式
};

ChartHistogram *ChartHistogram_New(apr_pool_t *pSupPool);
IChart *ChartHistogram2IChart(ChartHistogram *pInst);
void ChartHistogram_Free(ChartHistogram **ppInst);

#endif // !CHARTHISTOGRAM_H
