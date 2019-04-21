
#include <stdio.h>
#include "GifImage.h"


struct GifImage_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //实现接口
    Image m_img;

    //桥接类实例指针
    ImageImp *m_pImgImp;
};

static void Free(Image **ppImg)
{
    GifImage_Free(&(GifImage *)(*ppImg)->pImplicit);
    *ppImg = NULL;
}

static void SetImageImp(Image *pImg, ImageImp *pImgImp)
{
    ((GifImage *)pImg->pImplicit)->pFld->m_pImgImp = pImgImp;
}
static void ParseFile(Image *pImg, const char *const pFileName)
{
    GifImage *pInst = (GifImage *)pImg->pImplicit;

    //解析文件，成为图像像素矩阵
    Matrix *mat = Matrix_New(pInst->pFld->m_pPool);
    printf("解析Gif图像成为像素矩阵后，");

    //调用桥接方法，在指定的平台上绘制图像像素矩阵
    pInst->pFld->m_pImgImp->DoPaint(pInst->pFld->m_pImgImp, mat);

    ////Matrix类实例在GifImage的内存池中创建，
    ////随GifImage的实例销毁而销毁
    ////因此可不用主动释放
    //Matrix_Free(&mat);
}

GifImage * GifImage_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    GifImage *pInst = (GifImage *)apr_palloc(pPool, sizeof(GifImage));

    pInst->pFld = (GifImage_Fld *)apr_palloc(pPool, sizeof(GifImage_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_img.pImplicit = pInst;
    pInst->pFld->m_img.Free = Free;

    //桥接对象指针
    pInst->pFld->m_pImgImp = NULL;

    pInst->pFld->m_img.SetImageImp = SetImageImp;
    pInst->pFld->m_img.ParseFile = ParseFile;

    return pInst;
}

Image * GifImage2Image(GifImage * pInst)
{
    return &(pInst->pFld->m_img);
}

void GifImage_Free(GifImage ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);

    *ppInst = NULL;
}
