
#include "ActorBuilderDetail.h"

static Actor *pInst = NULL;

static void BuildRoleType()
{
    pInst->SetRole(pInst, ROLE_DEVIL);
}

static void BuildGenderType()
{
    pInst->SetGender(pInst, GENDER_MAN);
}

static void BuildFace()
{
    pInst->SetFace(pInst, "Horrible");
}

static void BuildCosutme()
{
    pInst->SetCostume(pInst, "Gothic");
}

static void BuildHairStyle()
{
    pInst->SetHairStyle(pInst, "Black");
}

static Actor *CreateActor()
{
    return pInst;
}

ActorBuilder *GetDevilBuilder(apr_pool_t *pPool, ActorBuilder *pMemIn)
{
    pInst = Actor_New(pPool);

    pMemIn->BuildRoleType = BuildRoleType;
    pMemIn->BuildGenderType = BuildGenderType;
    pMemIn->BuildFace = BuildFace;
    pMemIn->BuildCostume = BuildCosutme;
    pMemIn->BuildHairStyle = BuildHairStyle;

    pMemIn->CreateActor = CreateActor;

    return pMemIn;
}