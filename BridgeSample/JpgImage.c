
#include <stdio.h>
#include "JpgImage.h"


struct JpgImage_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //实现接口
    Image m_img;

    //桥接类指针
    ImageImp *m_pImgImp;
};

static void Free(Image **ppImg)
{
    JpgImage_Free(&(JpgImage *)(*ppImg)->pImplicit);
    *ppImg = NULL;
}

static void SetImageImp(Image *pImg, ImageImp *pImgImp)
{
    //注入桥接类实例
    ((JpgImage *)pImg->pImplicit)->pFld->m_pImgImp = pImgImp;
}
static void ParseFile(Image *pImg, const char *const pFileName)
{
    JpgImage *pInst = (JpgImage *)pImg->pImplicit;

    //模拟解析图片数据为图像像素矩阵
    Matrix *mat = Matrix_New(pInst->pFld->m_pPool);
    puts("解析jpg格式图像为像素矩阵后，");

    //调用桥接类实例的方法，实现在不同的平台上绘制图像像素矩阵
    pInst->pFld->m_pImgImp->DoPaint(pInst->pFld->m_pImgImp, mat);

    //Matrix_Free(&mat);
}

JpgImage * JpgImage_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    JpgImage *pInst = (JpgImage *)apr_palloc(pPool, sizeof(JpgImage));

    pInst->pFld = (JpgImage_Fld *)apr_palloc(pPool, sizeof(JpgImage_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_img.pImplicit = pInst;
    pInst->pFld->m_img.Free = Free;
    
    //桥接类实例指针必须初始化为null
    pInst->pFld->m_pImgImp = NULL;

    pInst->pFld->m_img.SetImageImp = SetImageImp;
    pInst->pFld->m_img.ParseFile = ParseFile;

    return pInst;
}

Image * JpgImage2Image(JpgImage * pInst)
{
    return &(pInst->pFld->m_img);
}

void JpgImage_Free(JpgImage ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);

    *ppInst = NULL;
}
