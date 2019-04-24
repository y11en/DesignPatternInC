
#include "ChartPie.h"

struct ChartPie_Fld
{
	apr_pool_t *m_pPool;

	IChart m_chart;
};

static void Free(IChart **ppchart)
{
	if (!ppchart || !(*ppchart))
	{
		return;
	}

	ChartPie_Free(&(ChartPie *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

static void Display()
{
	printf("显示饼状图！");
}

ChartPie * ChartPie_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	ChartPie *pInst = apr_palloc(pPool, sizeof(ChartPie));

	pInst->pFld = apr_palloc(pPool, sizeof(ChartPie_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	//初始化私有成员变量

	//初始化公共方法

	return pInst;
}

IChart * ChartPie2IChart(ChartPie * pInst)
{
	return &(pInst->pFld->m_chart);
}

void ChartPie_Free(ChartPie ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
