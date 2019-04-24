
#include <stdio.h>
#include "ImageJpg.h"


struct ImageJpg_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //实现接口
    IImage m_image;

    //桥接类指针
    IImageImp *m_pBridge;
};

static void Free(IImage **ppImage)
{
    ImageJpg_Free(&(ImageJpg *)(*ppImage)->pImplicit);
    *ppImage = NULL;
}

static void SetImageImp(IImage *pImage, IImageImp *pImgImp)
{
    //注入桥接类实例
    ((ImageJpg *)pImage->pImplicit)->pFld->m_pBridge = pImgImp;
}
static void ParseFile(IImage *pImage, const char *const pFileName)
{
    ImageJpg *pInst = (ImageJpg *)pImage->pImplicit;

    //模拟解析图片数据为图像像素矩阵
    Matrix *mat = Matrix_New(pInst->pFld->m_pPool);
    puts("解析jpg格式图像为像素矩阵后，");

    //调用桥接类实例的方法，实现在不同的平台上绘制图像像素矩阵
    pInst->pFld->m_pBridge->DoPaint(pInst->pFld->m_pBridge, mat);

    Matrix_Free(&mat);
}

ImageJpg * ImageJpg_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    ImageJpg *pInst = apr_palloc(pPool, sizeof(ImageJpg));

    pInst->pFld = apr_palloc(pPool, sizeof(ImageJpg_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_image.pImplicit = pInst;
    pInst->pFld->m_image.Free = Free;

    pInst->pFld->m_image.SetImageImp = SetImageImp;
    pInst->pFld->m_image.ParseFile = ParseFile;
    
    //桥接类实例指针必须初始化为null
    pInst->pFld->m_pBridge = NULL;

    return pInst;
}

IImage * ImageJpg2IImage(ImageJpg * pInst)
{
    return &(pInst->pFld->m_image);
}

void ImageJpg_Free(ImageJpg ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
