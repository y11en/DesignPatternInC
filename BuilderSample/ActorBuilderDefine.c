
#include "ActorBuilderDetail.h"

ActorBuilder *GetBuilder(apr_pool_t *pPool, BuilderType type, ActorBuilder *pMemIn)
{
	switch (type)
	{
	case BUILDER_NULL:
		return NULL;
	case BUILDER_ANGLE:
		return GetAngleBuilder(pPool, pMemIn);
	case BUILDER_DEVIL:
        return GetDevilBuilder(pPool, pMemIn);
	case BUILDER_HERO:
        return GetHeroBuilder(pPool, pMemIn);
	default:
		return NULL;
	}
}