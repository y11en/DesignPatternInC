
#include "ChartHistogram.h"

struct ChartHistogram_Fld
{
	apr_pool_t *m_pPool;

	//继承接口：接口结构类型变量声明
	IChart m_chart;
};

//继承接口：实现方法
static void Free(IChart **ppchart)
{
	if (!ppchart || !(*ppchart))
	{
		return;
	}

	/*这条注释是2019年1月写的，说明的内容与当前代码本不相关，留在这只是为了提醒自己需要注意一些问题*/
	//!!!!!!!!!!!!不能这样调用
	//HistogramChart_Free(&((HistogramChart *)(pchart->pImplicit)));
	//这样会导致在释放完所有占用内存之前，释放所需指针被置为“空”，导致无法完全释放。

	ChartHistogram_Free(&(ChartHistogram *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

//继承接口：实现方法
static void Display()
{
	printf("显示柱状图！");
}

ChartHistogram *ChartHistogram_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	ChartHistogram *pInst = apr_palloc(pPool, sizeof(ChartHistogram));
	
	pInst->pFld = apr_palloc(pPool, sizeof(ChartHistogram_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	return pInst;
}

IChart *ChartHistogram2IChart(ChartHistogram * pInst)
{
	return &(pInst->pFld->m_chart);
}

void ChartHistogram_Free(ChartHistogram ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
