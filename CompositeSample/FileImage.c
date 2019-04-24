
#include <stdio.h>
#include <apr_strings.h>
#include "FileImage.h"

//方法、属性声明

struct FileImage_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //继承接口
    IFile m_file;

    //文件名称
    char *m_pName;
};

//实现接口方法
static void Free(IFile **ppFile)
{
	FileImage_Free(&(FileImage *)(*ppFile)->pImplicit);
    *ppFile = NULL;
}

//实现接口方法
static void Add(IFile *pFile, IFile *pAdd)
{
    puts("图像文件不支持添加子文件操作。");
}

//实现接口方法
static void Remove(IFile *pFile, IFile *pRmv)
{
    puts("图像文件不支持删除子文件操作。");
}

//实现接口方法
static IFile *GetChild(IFile *pFile, int nIndex)
{
    puts("图像文件不含有子文件。");
    return NULL;
}

static void KillVirus(IFile *pFile)
{
	FileImage *pInst = (FileImage *)pFile->pImplicit;

    //模拟对图片文件进行杀毒
    printf("对图片文件%s进行杀毒。\n", pInst->pFld->m_pName);
}

FileImage * FileImage_New(apr_pool_t * pSupPool, const char * const pName)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	FileImage *pInst = apr_palloc(pPool, sizeof(FileImage));
    
    pInst->pFld = apr_palloc(pPool, sizeof(FileImage_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_file.pImplicit = pInst;
    pInst->pFld->m_file.Free = Free;
    pInst->pFld->m_pName = apr_pstrdup(pPool, pName);

    pInst->pFld->m_file.Add = Add;
    pInst->pFld->m_file.Remove = Remove;
    pInst->pFld->m_file.GetChild = GetChild;
    pInst->pFld->m_file.KillVirus = KillVirus;

    return pInst;
}

IFile * FileImage2IFile(FileImage * pInst)
{
    return &(pInst->pFld->m_file);
}

void FileImage_Free(FileImage ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
