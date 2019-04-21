
#include <apr_strings.h>
#include "UtilType.h"


char *RoleType_GetName(apr_pool_t *pPool, RoleType type)
{
    switch (type)
    {
    case ROLE_NULL:
        return apr_pstrdup(pPool, "ROLE_NULL");
    case ROLE_ANGLE:
        return apr_pstrdup(pPool, "ROLE_ANGLE");
    case ROLE_DEVIL:
        return apr_pstrdup(pPool, "ROLE_DEVIL");
    case ROLE_HERO:
        return apr_pstrdup(pPool, "ROLE_HERO");
    default:
        return apr_pstrdup(pPool, "ROLE_NULL");
    }
}

RoleType RoleType_GetValue(const char * const pValue)
{
	if (!strcmp(pValue, "ROLE_NULL"))
	{
		return ROLE_NULL;
	}
	if (!strcmp(pValue, "ROLE_ANGLE"))
	{
		return ROLE_ANGLE;
	}
	if (!strcmp(pValue, "ROLE_DEVIL"))
	{
		return ROLE_DEVIL;
	}if (!strcmp(pValue, "ROLE_HERO"))
	{
		return ROLE_HERO;
	}

	//default
	return ROLE_NULL;
}

char *GenderType_GetName(apr_pool_t *pPool, GenderType type)
{
    switch (type)
    {
    case GENDER_NULL:
        return apr_pstrdup(pPool, "GENDER_NULL");
    case GENDER_WOMAN:
        return apr_pstrdup(pPool, "GENDER_WOMAN");
    case GENDER_MAN:
        return apr_pstrdup(pPool, "GENDER_MAN");
    default:
        return apr_pstrdup(pPool, "GENDER_NULL");
    }
}

GenderType GenderType_GetValue(const char * const pValue)
{
    if (!strcmp(pValue, "GENDER_NULL"))
    {
        return GENDER_NULL;
    }
	if (!strcmp(pValue, "GENDER_MAN"))
	{
		return GENDER_MAN;
	}
	if (!strcmp(pValue, "GENDER_WOMAN"))
	{
		return GENDER_WOMAN;
	}

	//default
	return GENDER_NULL;
}