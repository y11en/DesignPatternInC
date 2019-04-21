
#include <apr_pools.h>
#include "Actor.h"

#ifndef ACTORBUILDER_H
#define ACTORBUILDER_H


typedef enum BuilderType BuilderType;

enum BuilderType
{
	BUILDER_NULL = 0,
	BUILDER_ANGLE = 1,
	BUILDER_DEVIL = 2,
	BUILDER_HERO = 3
};


typedef struct ActorBuilder ActorBuilder;

struct ActorBuilder
{
    //建造复杂对象的各个部分的方法
    void (* BuildRoleType)();
    void (* BuildGenderType)();
    void (* BuildFace)();
    void (* BuildCostume)();
    void (* BuildHairStyle)();

    //获取建造的对象
    Actor *(* CreateActor)();
};

//提供内存池入参，供所要建造的复杂对象内部使用
ActorBuilder *GetBuilder(apr_pool_t *pPool, BuilderType type, ActorBuilder *pMemIn);

#endif // !ACTORBUILDER_H
