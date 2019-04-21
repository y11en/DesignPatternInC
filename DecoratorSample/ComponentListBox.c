
#include <stdio.h>
#include "ComponentListBox.h"

//属性、方法声明

struct ComponentListBox_Fld
{
    //类实例专用内存池
    apr_pool_t *m_pPool;

    //继承接口
    IComponent m_component;
};

//实现接口方法
static void Free(IComponent **ppComponent)
{
    ComponentListBox_Free(&((ComponentListBox *)(*ppComponent)->pImplicit));
    *ppComponent = NULL;
}
//实现接口方法
static void Display(IComponent *pComponent)
{
    //ComponentListBox *pInst = (ComponentListBox *)pComponent->pImplicit;

    puts("显示列表框。");
}

ComponentListBox * ComponentListBox_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    ComponentListBox *pInst = apr_palloc(pPool, sizeof(ComponentListBox));

    pInst->pFld = apr_palloc(pPool, sizeof(ComponentListBox_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_component.pImplicit = pInst;
    pInst->pFld->m_component.Free = Free;

    pInst->pFld->m_component.Display = Display;

    return pInst;
}

IComponent * ComponentListBox2IComponent(ComponentListBox * pInst)
{
    return &(pInst->pFld->m_component);
}

void ComponentListBox_Free(ComponentListBox **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
