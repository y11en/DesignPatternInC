
#include <stdio.h>
#include "Emperor.h"

//单例
static Emperor *pSingleton = NULL;

struct Emperor_Fld
{
	//类实例专用内存池
	apr_pool_t *m_pPool;
};

//属性

//私有方法

//公有方法
static void Say(Emperor *pInst)
{
    printf("I\'m the great emperor!\n");
}

//私有构造方法
static Emperor *Emperor_New(apr_pool_t *pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

    Emperor *pInst = apr_palloc(pPool, sizeof(Emperor));

    pInst->pFld = apr_palloc(pPool, sizeof(Emperor_Fld));
	pInst->pFld->m_pPool = pPool;

    pInst->Say = Say;

    return pInst;
}

Emperor * GetEmperorInstance(apr_pool_t *pSupPool)
{
    //高并发时，最好先实例化和初始化单例，
    //否则可能出现多个单例的情况，
    //因为对象创建存在一个过程，需要花费一定时间
    return pSingleton ? pSingleton : (pSingleton = Emperor_New(pSupPool));
}

void Emperor_Free(Emperor ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);

    *ppInst = NULL;
}
