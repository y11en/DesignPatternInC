
#include <stdbool.h>
#include <apr_pools.h>


#ifndef VALIDATOR_H
#define VALIDATOR_H

typedef struct Validator_Fld Validator_Fld;
typedef struct Validator Validator;

struct Validator
{
	Validator_Fld *pFld;

	bool (* Validate)(Validator *pInst, const char *pUserID);
};

Validator *Validator_New(apr_pool_t *pSupPool);
void Validator_Free(Validator **ppInst);

#endif // !VALIDATOR_H
