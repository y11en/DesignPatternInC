
#include <apr_pools.h>
#include "IDiscount.h"


#ifndef DISCOUNTSTUDENT_H
#define DISCOUNTSTUDENT_H

typedef struct DiscountStudent_Fld DiscountStudent_Fld;
typedef struct DiscountStudent DiscountStudent;

struct DiscountStudent
{
    DiscountStudent_Fld *pFld;
};

DiscountStudent *DiscountStudent_New(apr_pool_t *pSupPool);
IDiscount *DiscountStudent2IDiscount(DiscountStudent *pInst);
void DiscountStudent_Free(DiscountStudent **ppInst);

#endif // !DISCOUNTSTUDENT_H
