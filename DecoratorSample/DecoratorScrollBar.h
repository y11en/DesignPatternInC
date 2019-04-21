
#include <apr_pools.h>
#include "IComponent.h"


#ifndef DECORATORSCROLLBAR_H
#define DECORATORSCROLLBAR_H

typedef struct DecoratorScrollBar_Fld DecoratorScrollBar_Fld;
typedef struct DecoratorScrollBar DecoratorScrollBar;

struct DecoratorScrollBar
{
    DecoratorScrollBar_Fld *pFld;
};

DecoratorScrollBar *DecoratorScrollBar_New(apr_pool_t *pSupPool, IComponent *pComponent);
IComponent *DecoratorScrollBar2IComponent(DecoratorScrollBar *pInst);
void DecoratorScrollBar_Free(DecoratorScrollBar **ppInst);

#endif // !DECORATORSCROLLBAR_H
