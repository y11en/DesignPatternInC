
#include <stdio.h>
#include <apr_pools.h>
#include "ActorBuilderControl.h"


int main(int argc, char **argv)
{
    apr_pool_t *pPool;

    apr_initialize();

    apr_pool_create(&pPool, NULL);

	ActorBuilder builder;
	Actor *actor = ConstructActorByBuilder(GetBuilder(pPool, BUILDER_ANGLE, &builder));

	printf("RoleType: %s\n", RoleType_GetName(pPool, actor->GetRole(actor)));
	printf("Gender: %s\n", GenderType_GetName(pPool, actor->GetGender(actor)));
	printf("Face: %s\n", actor->GetFace(actor, pPool));
	printf("Costume: %s\n", actor->GetCostume(actor, pPool));
	printf("HairStyle: %s\n", actor->GetHairStyle(actor, pPool));

	actor->SayLines();
	actor->Act(actor);

	Actor_Free(&actor);

    puts("//////////////////////////////////////////////////////////");

    ActorBuilder builder2;
    Actor *actor2 = ConstructActorByBuilder(GetBuilder(pPool, BUILDER_DEVIL, &builder2));

    printf("RoleType: %s\n", RoleType_GetName(pPool, actor2->GetRole(actor2)));
    printf("Gender: %s\n", GenderType_GetName(pPool, actor2->GetGender(actor2)));
    printf("Face: %s\n", actor2->GetFace(actor2, pPool));
    printf("Costume: %s\n", actor2->GetCostume(actor2, pPool));
    printf("HairStyle: %s\n", actor2->GetHairStyle(actor2, pPool));

    actor2->SayLines();
    actor2->Act(actor2);

    Actor_Free(&actor2);

    puts("//////////////////////////////////////////////////////////");

    ActorBuilder builder3;
    Actor *actor3 = ConstructActorByBuilder(GetBuilder(pPool, BUILDER_HERO, &builder3));

    printf("RoleType: %s\n", RoleType_GetName(pPool, actor3->GetRole(actor3)));
    printf("Gender: %s\n", GenderType_GetName(pPool, actor3->GetGender(actor3)));
    printf("Face: %s\n", actor3->GetFace(actor3, pPool));
    printf("Costume: %s\n", actor3->GetCostume(actor3, pPool));
    printf("HairStyle: %s\n", actor3->GetHairStyle(actor3, pPool));

    actor3->SayLines();
    actor3->Act(actor3);

    Actor_Free(&actor3);

    apr_pool_destroy(pPool);

    apr_terminate();

	return 0;
}