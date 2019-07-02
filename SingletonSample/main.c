
#include <stdio.h>
#include <apr_pools.h>
#include "Emperor.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;
	//apr_status_t retVal;

	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

    //单例测试
    Emperor *yinZheng = GetEmperorInstance(pMemPool);
    Emperor *yinZheng2 = GetEmperorInstance(pMemPool);
    
    yinZheng->Say(yinZheng);
    yinZheng2->Say(yinZheng2);

    Emperor_Free(&yinZheng);

	//单例，不要释放第二次
	//LoadBalancer_Free(&balancer2);

	apr_pool_destroy(pMemPool);

	apr_terminate();

    return EXIT_SUCCESS;
}