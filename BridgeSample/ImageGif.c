
#include <stdio.h>
#include "ImageGif.h"


struct ImageGif_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //实现接口
    IImage m_image;

    //桥接类实例指针
    IImageImp *m_pBridge;
};

static void Free(IImage **ppImage)
{
    ImageGif_Free(&(ImageGif *)(*ppImage)->pImplicit);
    *ppImage = NULL;
}

static void SetImageImp(IImage *pImage, IImageImp *pImgImp)
{
    ((ImageGif *)pImage->pImplicit)->pFld->m_pBridge = pImgImp;
}
static void ParseFile(IImage *pImage, const char *const pFileName)
{
    ImageGif *pInst = (ImageGif *)pImage->pImplicit;

    //解析文件，成为图像像素矩阵
    Matrix *mat = Matrix_New(pInst->pFld->m_pPool);
    printf("解析Gif图像成为像素矩阵后，");

    //调用桥接方法，在指定的平台上绘制图像像素矩阵
    pInst->pFld->m_pBridge->DoPaint(pInst->pFld->m_pBridge, mat);

    Matrix_Free(&mat);
}

ImageGif * ImageGif_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    ImageGif *pInst = apr_palloc(pPool, sizeof(ImageGif));

    pInst->pFld = apr_palloc(pPool, sizeof(ImageGif_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_image.pImplicit = pInst;
    pInst->pFld->m_image.Free = Free;

    pInst->pFld->m_image.SetImageImp = SetImageImp;
    pInst->pFld->m_image.ParseFile = ParseFile;

    //桥接对象指针
    pInst->pFld->m_pBridge = NULL;

    return pInst;
}

IImage * ImageGif2IImage(ImageGif * pInst)
{
    return &(pInst->pFld->m_image);
}

void ImageGif_Free(ImageGif ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
