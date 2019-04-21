
#include <stdio.h>
#include "BmpImage.h"


struct BmpImage_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

	//实现接口
	Image m_Img;

	//桥接对象指针
	ImageImp *m_pImgImp;
};

static void Free(Image **ppImg)
{
    BmpImage_Free(&(BmpImage *)(*ppImg)->pImplicit);
    *ppImg = NULL;
}

//实现接口方法
static void SetImageImp(Image *pImg, ImageImp *pImgImp)
{
    ((BmpImage *)pImg->pImplicit)->pFld->m_pImgImp = pImgImp;
}
//实现接口方法
static void ParseFile(Image *pImg, const char *const pFileName)
{
    BmpImage *pInst = (BmpImage *)pImg->pImplicit;

	//模拟解析Bmp图片，并生成Matrix矩阵
	Matrix *mat = Matrix_New(pInst->pFld->m_pPool);

	printf("解析Bmp格式图片，");
	
	//解析完成后，使用桥接的对象实例进行处理
	pInst->pFld->m_pImgImp->DoPaint(pInst->pFld->m_pImgImp, mat);
    
    ////不用释放
    //Matrix_Free(&mat);
}

BmpImage * BmpImage_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	BmpImage *pInst = (BmpImage *)apr_palloc(pPool, sizeof(BmpImage));

	pInst->pFld = (BmpImage_Fld *)apr_palloc(pPool, sizeof(BmpImage_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_Img.pImplicit = pInst;
    pInst->pFld->m_Img.Free = Free;

    //桥接对象指针
	pInst->pFld->m_pImgImp = NULL;

	pInst->pFld->m_Img.SetImageImp = SetImageImp;
	pInst->pFld->m_Img.ParseFile = ParseFile;

	return pInst;
}

Image * BmpImage2Image(BmpImage * pInst)
{
	return &(pInst->pFld->m_Img);
}

void BmpImage_Free(BmpImage ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
