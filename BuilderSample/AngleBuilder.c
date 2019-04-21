
#include "ActorBuilderDetail.h"

static Actor *pInst = NULL;

static void BuildRoleType()
{
	pInst->SetRole(pInst, ROLE_ANGLE);
}

static void BuildGenderType()
{
	pInst->SetGender(pInst, GENDER_WOMAN);
}

static void BuildFace()
{
	pInst->SetFace(pInst, "Beautiful face~~");
}

static void BuildCostume()
{
	pInst->SetCostume(pInst, "Classical");
}

static void BuildHairStyle()
{
	pInst->SetHairStyle(pInst, "Long blond hair.");
}

static Actor *CreateActor()
{
	return pInst;
}

ActorBuilder * GetAngleBuilder(apr_pool_t *pPool, ActorBuilder *pMemIn)
{
	pInst = Actor_New(pPool);

	//局部变量，调用完成后，即被释放掉
	//ActorBuilder builder;
	//因此，不能在此处创建，然后返回指针
	//return &builder//!!!!!!!错误


	pMemIn->BuildRoleType = BuildRoleType;
	pMemIn->BuildGenderType = BuildGenderType;
	pMemIn->BuildFace = BuildFace;
	pMemIn->BuildCostume = BuildCostume;
	pMemIn->BuildHairStyle = BuildHairStyle;

	pMemIn->CreateActor = CreateActor;

	return pMemIn;
}
