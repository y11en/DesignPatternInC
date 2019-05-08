
#include <malloc.h>
#include <apr_strings.h>
#include "Actor.h"


//必要的属性、方法声明

struct Actor_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    RoleType m_eRole;
    GenderType m_eGender;
    char *m_pFace;
    char *m_pCostume;
    char *m_pHairStyle;
};

//Properties
RoleType GetRole(Actor *pInst)
{
    return pInst->pFld->m_eRole;
}
static void SetRole(Actor *pInst, RoleType eRole)
{
    pInst->pFld->m_eRole = eRole;
}
static GenderType GetGender(Actor *pInst)
{
    return pInst->pFld->m_eGender;
}
static void SetGender(Actor *pInst, GenderType eGender)
{
    pInst->pFld->m_eGender = eGender;
}
static char *GetFace(Actor *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pFace);
}
static void SetFace(Actor *pInst, const char *const pFace)
{
	free(pInst->pFld->m_pFace);
	pInst->pFld->m_pFace = memcpy(malloc(strlen(pFace) + 1), pFace, strlen(pFace) + 1);
}
static char * GetCostume(Actor *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pCostume);
}
static void SetCostume(Actor *pInst, const char *const pCostume)
{
	free(pInst->pFld->m_pCostume);	
	pInst->pFld->m_pCostume = memcpy(malloc(strlen(pCostume) + 1/*\0*/), pCostume, strlen(pCostume) + 1/*\0*/);
}
static char * GetHairStyle(Actor *pInst, apr_pool_t *pPool)
{
    return apr_pstrdup(pPool, (const char *)pInst->pFld->m_pHairStyle);
}
static void SetHairStyle(Actor *pInst, const char *const pHairStyle)
{
	free(pInst->pFld->m_pHairStyle);
	pInst->pFld->m_pHairStyle = memcpy(malloc(strlen(pHairStyle) + 1), pHairStyle, strlen(pHairStyle) + 1);
}

//Private Methods

//Public Methods
static void SayLines(Actor *pInst)
{
    puts("Oh, Juliet~~\n");
}

static void Act(Actor *pInst)
{
    char *pRole = NULL;
    switch (pInst->pFld->m_eRole)
    {
    case ROLE_NULL:
    {
		pRole = &"Nothing";
    }
    break;
    case ROLE_ANGLE:
    {
        pRole = &"Angle";
    }
    break;
    case ROLE_DEVIL:
    {
        pRole = &"Devil";
    }
    break;
    case ROLE_HERO:
    {
        pRole = &"Hero";
    }
    break;
    default:
    {
        pRole = &"Nothing";
    }
    break;
    }

    printf("I\'m acting as %s.\n", pRole);
}

Actor * Actor_New(apr_pool_t *pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Actor *pInst = (Actor *)apr_palloc(pPool, sizeof(Actor));
    
    pInst->pFld = (Actor_Fld *)apr_palloc(pPool, sizeof(Actor_Fld));
    pInst->pFld->m_pPool = pPool;

	pInst->pFld->m_eGender = GENDER_MAN;
	pInst->pFld->m_eRole = ROLE_HERO;
	pInst->pFld->m_pFace = memcpy(malloc(sizeof("handsome")), "handsome", sizeof("handsome"));
	pInst->pFld->m_pCostume = memcpy(malloc(sizeof("Classical")), "Classical", sizeof("Classical"));
	pInst->pFld->m_pHairStyle = memcpy(malloc(sizeof("short black hair")), "short black hair", sizeof("short black hair"));

    pInst->GetRole = GetRole;
    pInst->SetRole = SetRole;
    pInst->GetGender = GetGender;
    pInst->SetGender = SetGender;
    pInst->GetFace = GetFace;
    pInst->SetFace = SetFace;
    pInst->GetCostume = GetCostume;
    pInst->SetCostume = SetCostume;
    pInst->GetHairStyle = GetHairStyle;
    pInst->SetHairStyle = SetHairStyle;

    pInst->SayLines = SayLines;
    pInst->Act = Act;

    return pInst;
}

void Actor_Free(Actor ** ppInst)
{
	free((*ppInst)->pFld->m_pFace);
	free((*ppInst)->pFld->m_pCostume);
	free((*ppInst)->pFld->m_pHairStyle);
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
