
#include <stdio.h>
#include <apr_strings.h>
#include "VideoFile.h"

//属性、方法声明
struct VideoFile_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IFile m_file;

    char *m_pName;
};

//实现接口方法
static void Free(IFile **ppFile)
{
    VideoFile_Free(&(VideoFile *)(*ppFile)->pImplicit);
    *ppFile = NULL;
}

//实现接口方法
static void Add(IFile *pFile, IFile *pAdd)
{
    puts("视频文件不支持添加子文件操作。");
}

//实现接口方法
static void Remove(IFile *pFile, IFile *pRmv)
{
    puts("视频文件不支持删除子文件操作。");
}

//实现接口方法
static IFile *GetChild(IFile *pFile, int nIndex)
{
    puts("视频文件不支持获取子文件操作。");
    return NULL;
}

//实现接口方法
static void KillVirus(IFile *pFile)
{
    VideoFile *pInst = (VideoFile *)pFile->pImplicit;

    //模拟杀毒
    printf("对视频文件%s进行杀毒.\n", pInst->pFld->m_pName);
}

VideoFile * VideoFile_New(apr_pool_t * pSupPool, const char * const pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    VideoFile *pInst = apr_palloc(pPool, sizeof(VideoFile));
    
    pInst->pFld = apr_palloc(pPool, sizeof(VideoFile_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_file.pImplicit = pInst;
    pInst->pFld->m_file.Free = Free;
    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);

    pInst->pFld->m_file.Add = Add;
    pInst->pFld->m_file.Remove = Remove;
    pInst->pFld->m_file.GetChild = GetChild;
    pInst->pFld->m_file.KillVirus = KillVirus;

    return pInst;
}

IFile * VideoFile2IFile(VideoFile * pInst)
{
    return &(pInst->pFld->m_file);
}

void VideoFile_Free(VideoFile ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
