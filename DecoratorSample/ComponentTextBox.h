
#include <apr_pools.h>
#include "IComponent.h"


#ifndef COMPONENTTEXTBOX_H
#define COMPONENTTEXTBOX_H

typedef struct ComponentTextBox_Fld ComponentTextBox_Fld;
typedef struct ComponentTextBox ComponentTextBox;

struct ComponentTextBox
{
    ComponentTextBox_Fld *pFld;
};

ComponentTextBox *ComponentTextBox_New(apr_pool_t *pSupPool);
IComponent *ComponentTextBox2IComponent(ComponentTextBox *pInst);
void ComponentTextBox_Free(ComponentTextBox **ppInst);

#endif // !COMPONENTTEXTBOX_H
