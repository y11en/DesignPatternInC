
#include <apr_pools.h>


#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix_Fld Matrix_Fld;
typedef struct Matrix Matrix;

struct Matrix
{
	Matrix_Fld *pFld;
};

Matrix *Matrix_New(apr_pool_t *pSupPool);
void Matrix_Free(Matrix **ppInst);

#endif // !MATRIX_H
