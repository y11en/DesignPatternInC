
#include <stdio.h>
#include "ImageImpWindows.h"


struct ImageImpWindows_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	IImageImp m_imageImp;
};

static void Free(IImageImp **ppImageImp)
{
    ImageImpWindows_Free(&(ImageImpWindows *)(*ppImageImp)->pImplicit);
    *ppImageImp = NULL;
}

static void DoPaint(IImageImp *pImageImp, Matrix *mat)
{
	puts("在Windows平台上，绘制图像像素矩阵.");
}

ImageImpWindows * ImageImpWindows_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

    ImageImpWindows *pInst = apr_palloc(pPool, sizeof(ImageImpWindows));

	pInst->pFld = apr_palloc(pPool, sizeof(ImageImpWindows_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_imageImp.pImplicit = pInst;
    pInst->pFld->m_imageImp.Free = Free;

	pInst->pFld->m_imageImp.DoPaint = DoPaint;

	return pInst;
}

IImageImp * ImageImpWindows2IImageImp(ImageImpWindows * pInst)
{
	return &(pInst->pFld->m_imageImp);
}

void ImageImpWindows_Free(ImageImpWindows ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
