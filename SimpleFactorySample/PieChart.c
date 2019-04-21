
#include "PieChart.h"


static void Display();
static void Free(IChart **ppchart);

struct PieChart_Fld
{
	apr_pool_t *m_pPool;

	IChart m_chart;
};

static void Display()
{
	printf("显示饼状图！");
}

static void Free(IChart **ppchart)
{
	if (!ppchart || !(*ppchart))
	{
		return;
	}

	PieChart_Free(&(PieChart *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

PieChart * const PieChart_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	PieChart *pInst = (PieChart *)apr_palloc(pPool, sizeof(PieChart));

	pInst->pFld = (PieChart_Fld *)apr_palloc(pPool, sizeof(PieChart_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	//初始化私有成员变量

	//初始化公共方法

	return pInst;
}

IChart * const PieChart2IChart(PieChart * pInst)
{
	return &(pInst->pFld->m_chart);
}

void PieChart_Free(PieChart ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
