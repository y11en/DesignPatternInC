
#include <apr_pools.h>


#ifndef ROLETYPE_H
#define ROLETYPE_H

typedef enum RoleType RoleType;

enum RoleType
{
    ROLE_NULL = 0,
    ROLE_ANGLE = 1,
	ROLE_DEVIL = 2,
	ROLE_HERO = 3
};

char *RoleType_GetName(apr_pool_t *pPool, RoleType type);
RoleType RoleType_GetValue(const char *const pValue);

#endif // !ROLETYPE_H


#ifndef GENDER_H
#define GENDER_H

typedef enum GenderType GenderType;

enum GenderType
{
    GENDER_NULL = 0,
    GENDER_MAN = 1,
	GENDER_WOMAN = 2
};

char *GenderType_GetName(apr_pool_t *pPool, GenderType type);
GenderType GenderType_GetValue(const char *const pValue);

#endif // !GENDER_H
