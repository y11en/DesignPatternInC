
#include <stdio.h>
#include "UnixImp.h"


struct UnixImp_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	//继承接口，只需声明成变量即可，无须声明称指针
	ImageImp m_ImgImp;
};

static void Free(ImageImp **ppImgImp)
{
    UnixImp_Free(&(UnixImp *)(*ppImgImp)->pImplicit);
    *ppImgImp = NULL;
}

//实现接口的方法
static void DoPaint(ImageImp *pImgImp, Matrix *mat)
{
    //UnixImp *pInst = (UnixImp *)pImgImp->pImplicit;
	puts("在Unix平台上绘制图片像素矩阵.");
}

UnixImp * UnixImp_New(apr_pool_t *pSubPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSubPool);

	UnixImp *pInst = (UnixImp *)apr_palloc(pPool, sizeof(UnixImp));

	pInst->pFld = (UnixImp_Fld *)apr_palloc(pPool, sizeof(UnixImp_Fld));
	pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_ImgImp.pImplicit = pInst;
    pInst->pFld->m_ImgImp.Free = Free;
	
	pInst->pFld->m_ImgImp.DoPaint = DoPaint;

	return pInst;
}

ImageImp * UnixImp2ImageImp(UnixImp * pInst)
{
	return &(pInst->pFld->m_ImgImp);
}

void UnixImp_Free(UnixImp ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
