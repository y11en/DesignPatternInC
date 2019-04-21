
#include <apr_pools.h>
#include "IComponent.h"

#ifndef DECORATORBLACKBORDER_H
#define DECORATORBLACKBORDER_H

typedef struct DecoratorBlackBorder_Fld DecoratorBlackBorder_Fld;
typedef struct DecoratorBlackBorder DecoratorBlackBorder;

struct DecoratorBlackBorder
{
    DecoratorBlackBorder_Fld *pFld;

    //透明装饰器，
    //继承接口时，不需要声明接口的公共方法
};

DecoratorBlackBorder *DecoratorBlackBorder_New(apr_pool_t *pSupPool, IComponent *pComponent);
IComponent *DecoratorBlackBorder2IComponent(DecoratorBlackBorder *pInst);
void DecoratorBlackBorder_Free(DecoratorBlackBorder **ppInst);

#endif // !DECORATORBLACKBORDER_H
