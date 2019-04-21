
#include <apr_pools.h>
#include "IComponent.h"


#ifndef COMPONENTLISTBOX_H
#define COMPONENTLISTBOX_H

typedef struct ComponentListBox_Fld ComponentListBox_Fld;
typedef struct ComponentListBox ComponentListBox;

struct ComponentListBox
{
    ComponentListBox_Fld *pFld;

    //因为控件通过接口类型调用，
    //因此这里不用声明继承得到的公共方法Display
};

ComponentListBox *ComponentListBox_New(apr_pool_t *pSupPool);
IComponent *ComponentListBox2IComponent(ComponentListBox *pInst);
void ComponentListBox_Free(ComponentListBox **ppInst);

#endif // !COMPONENTLISTBOX_H
