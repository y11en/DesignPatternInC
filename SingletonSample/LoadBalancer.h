
#include <apr_pools.h>

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

typedef struct LoadBalancer_Fld LoadBalancer_Fld;
typedef struct LoadBalancer LoadBalancer;

struct LoadBalancer
{
    LoadBalancer_Fld *pFld;

    void (* AddServer)(LoadBalancer *pInst, const char *const pServer);
    void (* RemoveServer)(LoadBalancer *pInst, const char *const pServer);
    int (* GetServerIndex)(LoadBalancer *pInst, const char* const pServer);
};

LoadBalancer *GetLoadBalancerInstance(apr_pool_t *pMemPool);
void LoadBalancer_Free(LoadBalancer **ppInst);

#endif // !LOADBALANCER_H
