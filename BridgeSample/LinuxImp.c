
#include <stdio.h>
#include "LinuxImp.h"


struct LinuxImp_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	//继承接口
	ImageImp m_ImgImp;
};

static void Free(ImageImp **ppImgImp)
{
    LinuxImp_Free(&(LinuxImp *)(*ppImgImp)->pImplicit);
    *ppImgImp = NULL;
}

//实现接口方法
static void DoPaint(ImageImp *pImgImp, Matrix *mat)
{
    //LinuxImp *pInst = (LinuxImp *)pImgImp->pImplicit;

	puts("在Linux平台上，绘制图像像素矩阵.");
}

LinuxImp * LinuxImp_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	LinuxImp *pInst = (LinuxImp *)apr_palloc(pPool, sizeof(LinuxImp));

	pInst->pFld = (LinuxImp_Fld *)apr_palloc(pPool, sizeof(LinuxImp_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_ImgImp.pImplicit = pInst;
    pInst->pFld->m_ImgImp.Free = Free;

	pInst->pFld->m_ImgImp.DoPaint = DoPaint;

	return pInst;
}

ImageImp * LinuxImp2ImageImp(LinuxImp * pInst)
{
	return &(pInst->pFld->m_ImgImp);
}

void LinuxImp_Free(LinuxImp ** ppInst)
{	
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
