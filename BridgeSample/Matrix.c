
#include "Matrix.h"

struct Matrix_Fld
{
    //类实例专用内存池
	apr_pool_t *m_pPool;
};

Matrix * Matrix_New(apr_pool_t *pSupPool)
{
	//创建当前类专用的内存池
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	//类实例
	Matrix *pInst = apr_palloc(pPool, sizeof(Matrix));

	//类数据域初始化
	pInst->pFld = apr_palloc(pPool, sizeof(Matrix_Fld));
	//类实例专用内存池
	pInst->pFld->m_pPool = pPool;

	return pInst;
}

void Matrix_Free(Matrix ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
