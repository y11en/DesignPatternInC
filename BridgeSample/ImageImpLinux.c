
#include <stdio.h>
#include "ImageImpLinux.h"


struct ImageImpLinux_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	//继承接口
	IImageImp m_imageImp;
};

static void Free(IImageImp **ppImageImp)
{
    ImageImpLinux_Free(&(ImageImpLinux *)(*ppImageImp)->pImplicit);
    *ppImageImp = NULL;
}

//实现接口方法
static void DoPaint(IImageImp *pImageImp, Matrix *pMat)
{
    //LinuxImp *pInst = (LinuxImp *)pImgImp->pImplicit;

	puts("在Linux平台上，绘制图像像素矩阵.");
}

ImageImpLinux * ImageImpLinux_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

    ImageImpLinux *pInst = apr_palloc(pPool, sizeof(ImageImpLinux));

	pInst->pFld = apr_palloc(pPool, sizeof(ImageImpLinux_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_imageImp.pImplicit = pInst;
    pInst->pFld->m_imageImp.Free = Free;

	pInst->pFld->m_imageImp.DoPaint = DoPaint;

	return pInst;
}

IImageImp *ImageImpLinux2IImageImp(ImageImpLinux * pInst)
{
	return &(pInst->pFld->m_imageImp);
}

void ImageImpLinux_Free(ImageImpLinux ** ppInst)
{	
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
