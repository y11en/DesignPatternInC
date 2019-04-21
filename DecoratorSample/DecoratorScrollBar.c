
#include <stdio.h>
#include "DecoratorScrollBar.h"

//属性、方法声明
static void SetScrollBar();

struct DecoratorScrollBar_Fld
{
    apr_pool_t *m_pPool;

    IComponent m_component;

    //外部注入的具体构件
    IComponent *m_pComponent;
};

//实现接口方法
static void Free(IComponent **ppComponent)
{
    DecoratorScrollBar_Free(&((DecoratorScrollBar *)(*ppComponent)->pImplicit));
    *ppComponent = NULL;
}

//实现接口方法
static void Display(IComponent *pComponent)
{
    DecoratorScrollBar *pInst = (DecoratorScrollBar *)pComponent->pImplicit;

    //装饰增强
    SetScrollBar();
    //调用构件的方法
    pInst->pFld->m_pComponent->Display(&(pInst->pFld->m_component));
}

//装饰构件
//这里实现透明装饰
static void SetScrollBar()
{
    puts("为构件增加进度条.");
}

DecoratorScrollBar * DecoratorScrollBar_New(apr_pool_t * pSupPool, IComponent * pComponent)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DecoratorScrollBar *pInst = apr_palloc(pPool, sizeof(DecoratorScrollBar));

    pInst->pFld = apr_palloc(pPool, sizeof(DecoratorScrollBar_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_component.pImplicit = pInst;
    pInst->pFld->m_component.Free = Free;

    pInst->pFld->m_component.Display = Display;
    pInst->pFld->m_pComponent = pComponent;

    return pInst;
}

IComponent * DecoratorScrollBar2IComponent(DecoratorScrollBar * pInst)
{
    return &(pInst->pFld->m_component);
}

void DecoratorScrollBar_Free(DecoratorScrollBar ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
