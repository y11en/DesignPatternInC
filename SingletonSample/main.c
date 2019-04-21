
#include <stdio.h>
#include <apr_pools.h>
#include "LoadBalancer.h"


int main(int argc, char **argv)
{
	apr_pool_t *pMemPool;
	//apr_status_t retVal;

	apr_initialize();

	apr_pool_create(&pMemPool, NULL);

    //单例测试
    LoadBalancer *balancer = GetLoadBalancerInstance(pMemPool);
    LoadBalancer *balancer2 = GetLoadBalancerInstance(pMemPool);
    printf("are the two balancers the same? %s\n", (balancer == balancer2 ? "true" : "false"));

    balancer->AddServer(balancer, "Server1");
    balancer->AddServer(balancer, "Server2");
    balancer->AddServer(balancer, "Server3");

    balancer2->RemoveServer(balancer2, "Server2");
    printf("Index of \"Server3\" is %d\n", balancer2->GetServerIndex(balancer2, "Server3"));

	LoadBalancer_Free(&balancer);

	//单例，不要释放第二次
	//LoadBalancer_Free(&balancer2);

	apr_pool_destroy(pMemPool);

	apr_terminate();

    return EXIT_SUCCESS;
}