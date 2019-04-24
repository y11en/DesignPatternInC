
#include <stdio.h>
#include "ImageBmp.h"


struct ImageBmp_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

	//实现接口
	IImage m_image;

	//桥接对象指针
	IImageImp *m_pBridge;
};

static void Free(IImage **ppImage)
{
    ImageBmp_Free(&(ImageBmp *)(*ppImage)->pImplicit);
    *ppImage = NULL;
}

//实现接口方法
static void SetImageImp(IImage *pImage, IImageImp *pImgImp)
{
    ((ImageBmp *)pImage->pImplicit)->pFld->m_pBridge = pImgImp;
}
//实现接口方法
static void ParseFile(IImage *pImage, const char *const pFileName)
{
    ImageBmp *pInst = (ImageBmp *)pImage->pImplicit;

	//模拟解析Bmp图片，并生成Matrix矩阵
	Matrix *mat = Matrix_New(pInst->pFld->m_pPool);

	printf("解析Bmp格式图片，");
	
	//解析完成后，使用桥接的对象实例进行处理
	pInst->pFld->m_pBridge->DoPaint(pInst->pFld->m_pBridge, mat);
    
    Matrix_Free(&mat);
}

ImageBmp * ImageBmp_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	ImageBmp *pInst = apr_palloc(pPool, sizeof(ImageBmp));

	pInst->pFld = apr_palloc(pPool, sizeof(ImageBmp_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_image.pImplicit = pInst;
    pInst->pFld->m_image.Free = Free;

	pInst->pFld->m_image.SetImageImp = SetImageImp;
	pInst->pFld->m_image.ParseFile = ParseFile;

    //桥接对象指针
	pInst->pFld->m_pBridge = NULL;

	return pInst;
}

IImage * ImageBmp2IImage(ImageBmp * pInst)
{
	return &(pInst->pFld->m_image);
}

void ImageBmp_Free(ImageBmp ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
