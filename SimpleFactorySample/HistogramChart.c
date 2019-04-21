#include "HistogramChart.h"


static void Display();
static void Free(IChart **ppchart);

struct HistogramChart_Fld
{
	apr_pool_t *m_pPool;

	//继承接口：接口结构类型变量声明
	IChart m_chart;
};

//继承接口：实现方法
static void Display()
{
	printf("显示柱状图！");
}

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

	HistogramChart_Free(&(HistogramChart *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

HistogramChart *const HistogramChart_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	HistogramChart *pInst = (HistogramChart *)apr_palloc(pPool, sizeof(HistogramChart));
	
	pInst->pFld = (HistogramChart_Fld *)apr_palloc(pPool, sizeof(HistogramChart_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	return pInst;
}

IChart * const HistogramChart2IChart(HistogramChart * pInst)
{
	return &(pInst->pFld->m_chart);
}

void HistogramChart_Free(HistogramChart ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
