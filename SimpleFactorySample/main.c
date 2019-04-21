
#include <stdio.h>
#include <apr_pools.h>
#include "IChart.h"
#include "SimpleFactory.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;

	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

		IChart *chart = NULL;
	for (size_t i = 0; i < 1000000; i++)
	{
		chart = GetChart(pMemPool, CHART_HISTOGRAM);
		chart->Display();
		chart->Free(&chart);
	}

		chart = GetChart(pMemPool, CHART_LINE);//构造
		chart->Display();//使用
		chart->Free(&chart);//销毁

		chart = GetChart(pMemPool, CHART_PIE);
		chart->Display();
		chart->Free(&chart);

		if (!chart)
		{
			puts("\nNow IChart pointer \"chart\" is null.\n");
		}

	apr_pool_destroy(pMemPool);

	apr_terminate();

	return EXIT_SUCCESS;
}