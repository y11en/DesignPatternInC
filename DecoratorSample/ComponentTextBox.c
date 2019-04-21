
#include <stdio.h>
#include "ComponentTextBox.h"

//属性、方法声明

struct ComponentTextBox_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IComponent m_component;
};

//实现接口方法
static void Free(IComponent **ppComponent)
{
    ComponentTextBox_Free(&(ComponentTextBox *)(*ppComponent)->pImplicit);
    *ppComponent = NULL;
}

static void Display(IComponent *pComponent)
{
    //ComponentTextBox *pInst = (ComponentTextBox *)pComponent->pImplicit;

    puts("显示文本框。");
}

ComponentTextBox * ComponentTextBox_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    ComponentTextBox *pInst = apr_palloc(pPool, sizeof(ComponentTextBox));
    
    pInst->pFld = apr_palloc(pPool, sizeof(ComponentTextBox_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_component.pImplicit = pInst;
    pInst->pFld->m_component.Free = Free;

    pInst->pFld->m_component.Display = Display;

    return pInst;
}

IComponent * ComponentTextBox2IComponent(ComponentTextBox * pInst)
{
    return &(pInst->pFld->m_component);
}

void ComponentTextBox_Free(ComponentTextBox ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
