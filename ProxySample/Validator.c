
#include <stdio.h>
#include "Validator.h"

struct Validator_Fld
{
	apr_pool_t *m_pPool;
};

static bool Validate(Validator *pInst, const char *pUserID)
{
	//模拟验证
	printf("在数据库中验证用户%s是否合法\n", pUserID);

	if (!strcmp(pUserID, "杨过"))
	{
		printf("通过验证。\n");
		return true;
	}
	else
	{
		printf("验证失败。\n");
		return false;
	}
}

Validator * Validator_New(apr_pool_t * pSupPool)
{
	apr_pool_t *pPool;
	apr_pool_create(&pPool, pSupPool);

	Validator *pInst = apr_palloc(pPool, sizeof(Validator));

	pInst->pFld = apr_palloc(pPool, sizeof(Validator_Fld));
	pInst->pFld->m_pPool = pPool;

	pInst->Validate = Validate;

	return pInst;
}

void Validator_Free(Validator ** ppInst)
{
	apr_pool_destroy((*ppInst)->pFld->m_pPool);
	*ppInst = NULL;
}
