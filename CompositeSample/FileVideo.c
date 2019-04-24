
#include <stdio.h>
#include <apr_strings.h>
#include "FileVideo.h"

//属性、方法声明
struct FileVideo_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IFile m_file;

    char *m_pName;
};

//实现接口方法
static void Free(IFile **ppFile)
{
	FileVideo_Free(&(FileVideo *)(*ppFile)->pImplicit);
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
	FileVideo *pInst = (FileVideo *)pFile->pImplicit;

    //模拟杀毒
    printf("对视频文件%s进行杀毒.\n", pInst->pFld->m_pName);
}

FileVideo * FileVideo_New(apr_pool_t * pSupPool, const char * const pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	FileVideo *pInst = apr_palloc(pPool, sizeof(FileVideo));
    
    pInst->pFld = apr_palloc(pPool, sizeof(FileVideo_Fld));
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

IFile * FileVideo2IFile(FileVideo * pInst)
{
    return &(pInst->pFld->m_file);
}

void FileVideo_Free(FileVideo ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
