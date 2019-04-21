
#include <apr_pools.h>
#include "IComponent.h"


#ifndef COMPONENTWINDOW_H
#define COMPONENTWINDOW_H

typedef struct ComponentWindow_Fld ComponentWindow_Fld;
typedef struct ComponentWindow ComponentWindow;

struct ComponentWindow
{
    ComponentWindow_Fld *pFld;
};

ComponentWindow *ComponentWindow_New(apr_pool_t *pSupPool);
IComponent *ComponentWindow2IComponent(ComponentWindow *pInst);
void ComponentWindow_Free(ComponentWindow **ppInst);

#endif // !COMPONENTWINDOW_H
