
#include <stdio.h>
#include "ImageImpUnix.h"


struct ImageImpUnix_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	//继承接口，只需声明成变量即可，无须声明称指针
	IImageImp m_imageImp;
};

static void Free(IImageImp **ppImageImp)
{
    ImageImpUnix_Free(&(ImageImpUnix *)(*ppImageImp)->pImplicit);
    *ppImageImp = NULL;
}

//实现接口的方法
static void DoPaint(IImageImp *pImageImp, Matrix *pMat)
{
    //UnixImp *pInst = (UnixImp *)pImgImp->pImplicit;
	puts("在Unix平台上绘制图片像素矩阵.");
}

ImageImpUnix * ImageImpUnix_New(apr_pool_t *pSubPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSubPool);

    ImageImpUnix *pInst = apr_palloc(pPool, sizeof(ImageImpUnix));

	pInst->pFld = apr_palloc(pPool, sizeof(ImageImpUnix_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_imageImp.pImplicit = pInst;
    pInst->pFld->m_imageImp.Free = Free;
	
	pInst->pFld->m_imageImp.DoPaint = DoPaint;

	return pInst;
}

IImageImp * ImageImpUnix2IImageImp(ImageImpUnix * pInst)
{
	return &(pInst->pFld->m_imageImp);
}

void ImageImpUnix_Free(ImageImpUnix ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
