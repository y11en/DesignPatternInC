
#include "ActorBuilderControl.h"

Actor *ConstructActorByBuilder(ActorBuilder *builder)
{
	builder->BuildRoleType();
	builder->BuildGenderType();
	builder->BuildFace();
	builder->BuildCostume();
	builder->BuildHairStyle();

	return builder->CreateActor();
}