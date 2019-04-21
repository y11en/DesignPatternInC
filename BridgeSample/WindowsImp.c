
#include <stdio.h>
#include "WindowsImp.h"


struct WindowsImp_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	ImageImp m_ImgImp;
};

static void Free(ImageImp **ppImgImp)
{
    WindowsImp_Free(&(WindowsImp *)(*ppImgImp)->pImplicit);
    *ppImgImp = NULL;
}

static void DoPaint(ImageImp *pImgImp, Matrix *mat)
{
	puts("在Windows平台上，绘制图像像素矩阵.");
}

WindowsImp * WindowsImp_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	WindowsImp *pInst = (WindowsImp *)apr_palloc(pPool, sizeof(WindowsImp));

	pInst->pFld = (WindowsImp_Fld *)apr_palloc(pPool, sizeof(WindowsImp_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_ImgImp.pImplicit = pInst;
    pInst->pFld->m_ImgImp.Free = Free;

	pInst->pFld->m_ImgImp.DoPaint = DoPaint;

	return pInst;
}

ImageImp * WindowsImp2ImageImp(WindowsImp * pInst)
{
	return &(pInst->pFld->m_ImgImp);
}

void WindowsImp_Free(WindowsImp ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
