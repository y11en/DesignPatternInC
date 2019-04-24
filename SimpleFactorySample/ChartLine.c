
#include "ChartLine.h"

struct ChartLine_Fld
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

	ChartLine_Free(&(ChartLine *)(*ppchart)->pImplicit);
	*ppchart = NULL;
}

static void Display()
{
	printf("显示折线图！");
}

ChartLine * ChartLine_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	ChartLine *pInst = apr_palloc(pPool, sizeof(ChartLine));
	
	pInst->pFld = apr_palloc(pPool, sizeof(ChartLine_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_chart.pImplicit = pInst;
	pInst->pFld->m_chart.Free = Free;

	pInst->pFld->m_chart.Display = Display;

	//私有变量的初始化

	//公有方法的初始化

	return pInst;
}

IChart * ChartLine2IChart(ChartLine * pInst)
{
	return &(pInst->pFld->m_chart);
}

void ChartLine_Free(ChartLine ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);	
	*ppInst = NULL;
}
