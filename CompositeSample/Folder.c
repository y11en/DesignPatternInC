
#include <stdio.h>
#include <apr_ring.h>
#include <apr_strings.h>
#include <apr_ring_ext.h>
#include "Folder.h"

/* 
 * 私有类型，类内部使用
 * IFile类型双向环链表定义
 */
GENERIC_RING(IFile)

//属性、方法声明

struct Folder_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	//继承接口
	IFile m_file;

    //文件夹名称
    char *m_pName;

    //子文件夹、文件链表
	RING(IFile) *m_pRingFiles;
};

//类私有方法
/* 将指针封装成其对应链表类型的元素类型 */
static RING_ELEM(IFile) *ConstructRingElement(apr_pool_t *pPool, IFile *pFile)
{
    RING_ELEM(IFile) *pElem = /* (RING_ELEM(IFile) *) */apr_palloc(pPool, sizeof(RING_ELEM(IFile)));
    pElem->pInst = pFile;
    return pElem;
}

//私有方法
/* 查找链表中是否存在给定的元素，如果存在，则返回元素的指针 */
static int FindElement(RING(IFile) *pRing, RING_ELEM(IFile) *pToFind)
{
    int nIndex = 0;
    RING_ELEM(IFile) *pIterate;
    for (pIterate = APR_RING_FIRST(pRing); pIterate != APR_RING_SENTINEL(pRing, RING_ELEM(IFile), RING_LINK); pIterate = APR_RING_NEXT(pIterate, RING_LINK))
    {
        nIndex++;

        if (pIterate == pToFind)
        {
            //链表中存在该元素，
            return nIndex;
        }
    }

    //链表中不存在该元素
    return nIndex = -1;
}

//实现接口方法
static void Free(IFile **ppFile)
{
	Folder_Free(&(Folder *)(*ppFile)->pImplicit);
	*ppFile = NULL;
}

//实现接口方法
static void Add(IFile *pFile, IFile *pAdd)
{
    Folder *pInst = (Folder *)pFile->pImplicit;

    int nIndex = 0;
    RING_ELEM(IFile) *pElem = ConstructRingElement(pInst->pFld->m_pPool, pAdd);
    if (FindElement(pInst->pFld->m_pRingFiles, pElem) != -1)
    {
        //如果存在该元素，则不添加
        puts("已经存在该元素，将不会添加。");
    }
    else
    {
        APR_RING_INSERT_TAIL(pInst->pFld->m_pRingFiles, pElem, RING_ELEM(IFile), RING_LINK);
        puts("添加成功。");
    }
}

//移除元素
static void Remove(IFile *pFile, IFile *pRmv)
{
    Folder *pInst = (Folder *)pFile->pImplicit;

    RING_ELEM(IFile) *pElem = ConstructRingElement(pInst->pFld->m_pPool, pRmv);

    if (FindElement(pInst->pFld->m_pRingFiles, pElem) != -1)
    {
        //找到该元素
        APR_RING_UNSPLICE(pElem, pElem, RING_LINK);
        puts("找到并删除了指定的元素");
    }
    else
    {
        puts("没要找到指定的需要删除的元素。");
    }
}

static IFile *GetChild(IFile *pFile, int nIndex)
{
    Folder *pInst = (Folder *)pFile->pImplicit;

    int nI = 0;
    RING_ELEM(IFile) *pIterate;
    for (pIterate = APR_RING_FIRST(pInst->pFld->m_pRingFiles); pIterate != APR_RING_SENTINEL(pInst->pFld->m_pRingFiles, RING_ELEM(IFile), RING_LINK); pIterate = APR_RING_NEXT(pIterate, RING_LINK))
    {
        if (nI == nIndex)
        {
            return pIterate->pInst;
        }
    }

    return NULL;
}

static void KillVirus(IFile *pFile)
{
    Folder *pInst = (Folder *)pFile->pImplicit;
    //模拟杀毒
    printf("对文件夹%s进行杀毒.\n", pInst->pFld->m_pName);

    RING_ELEM(IFile) *pIterate;
    for (pIterate = APR_RING_FIRST(pInst->pFld->m_pRingFiles); pIterate != APR_RING_SENTINEL(pInst->pFld->m_pRingFiles, RING_ELEM(IFile), RING_LINK); pIterate = APR_RING_NEXT(pIterate, RING_LINK))
    {
        //遍历子文件夹、文件，进行杀毒
        pIterate->pInst->KillVirus(pIterate->pInst);
    }
}

Folder * Folder_New(apr_pool_t * pSupPool, const char *const pName)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Folder *pInst = (Folder *)apr_palloc(pPool, sizeof(Folder));

	pInst->pFld = (Folder_Fld *)apr_palloc(pPool, sizeof(Folder_Fld));
	pInst->pFld->m_pPool = pPool;
	pInst->pFld->m_file.pImplicit = pInst;
	pInst->pFld->m_file.Free = Free;
    pInst->pFld->m_pName = apr_pstrdup(pInst->pFld->m_pPool, pName);
	pInst->pFld->m_pRingFiles = apr_palloc(pInst->pFld->m_pPool, sizeof(RING(IFile)));

	/*初始化环*/
	APR_RING_INIT(pInst->pFld->m_pRingFiles, RING_ELEM(IFile), RING_LINK);

    pInst->pFld->m_file.Add = Add;
    pInst->pFld->m_file.Remove = Remove;
    pInst->pFld->m_file.GetChild = GetChild;
    pInst->pFld->m_file.KillVirus = KillVirus;

	return pInst;
}

IFile * Folder2IFile(Folder * pInst)
{
    return &(pInst->pFld->m_file);
}

void Folder_Free(Folder ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

	*ppInst = NULL;
}
