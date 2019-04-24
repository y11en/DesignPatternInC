
#include <apr_tables.h>
#include <apr_strings.h>
#include "LoadBalancer.h"

//单例
static LoadBalancer *pSingleton = NULL;

struct LoadBalancer_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;

	apr_array_header_t *m_arr;
};

//属性

//私有方法

//公有方法
static void AddServer(LoadBalancer *pInst, const char *const pServer)
{
	*(const char **)apr_array_push(pInst->pFld->m_arr) = apr_pstrdup(pInst->pFld->m_pPool, pServer);
}
static void RemoveServer(LoadBalancer *pInst, const char *const pServer)
{
	for (int i = 0; i < pInst->pFld->m_arr->nelts; i++)
	{
		if (!strcmp(((const char **)pInst->pFld->m_arr->elts)[i], pServer))
		{
			//这里应该删除数组中的元素，
			//偷个懒，就打印一下语句好了。
			printf("Element %s found, and will be removed..\n", ((const char **)pInst->pFld->m_arr->elts)[i]);
			break;
		}
	}
}
static int GetServerIndex(LoadBalancer *pInst, const char* const pServer)
{
	for (int i = 0; i < pInst->pFld->m_arr->nelts; i++)
	{
		if (!strcmp(((const char **)pInst->pFld->m_arr->elts)[i], pServer))
		{
			//printf("Element %s found.\n", ((const char **)pInst->pFld->m_arr->elts)[i]);
			return i;
		}
	}

	return -1;
}

//私有构造方法
static LoadBalancer *LoadBalancer_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

    LoadBalancer *pInst = (LoadBalancer *)apr_palloc(pPool, sizeof(LoadBalancer));

    pInst->pFld = (LoadBalancer_Fld *)apr_palloc(pPool, sizeof(LoadBalancer));
	pInst->pFld->m_pPool = pPool;

	//创建动态字符串数组
	pInst->pFld->m_arr = apr_array_make(pInst->pFld->m_pPool, 20/*初始容量20*/, sizeof(const char *)/*每个元素都是字符串，存储字符串的指针*/);

    pInst->AddServer = AddServer;
    pInst->RemoveServer = RemoveServer;
    pInst->GetServerIndex = GetServerIndex;

    return pInst;
}

LoadBalancer * GetLoadBalancerInstance(apr_pool_t *pSupPool)
{
    return pSingleton ? pSingleton : (pSingleton = LoadBalancer_New(pSupPool));
}

void LoadBalancer_Free(LoadBalancer ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

    *ppInst = NULL;
}
