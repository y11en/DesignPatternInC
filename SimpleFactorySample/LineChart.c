
#include "LineChart.h"


static void Display();
static void Free(IChart **ppchart);

struct LineChart_Fld
{
	apr_pool_t *m_pPool;

	IChart m_chart;
};

static void Display()
{
	printf("显示折线图！");
}

static void Free(IChart **ppchart)
{
	if (!ppchart || !(*ppchart))
	{
		return;
	}

	LineChart_Free(&(LineChart *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

LineChart * const LineChart_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	LineChart *pInst = (LineChart *)apr_palloc(pPool, sizeof(LineChart));
	
	pInst->pFld = (LineChart_Fld *)apr_palloc(pPool, sizeof(LineChart_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	//私有变量的初始化

	//公有方法的初始化

	return pInst;
}

IChart * const LineChart2IChart(LineChart * pInst)
{
	return &(pInst->pFld->m_chart);
}

void LineChart_Free(LineChart ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	
	*ppInst = NULL;
}
