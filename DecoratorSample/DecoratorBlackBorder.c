
#include "DecoratorBlackBorder.h"

//属性、方法声明
static void SetBlackBorder();

struct DecoratorBlackBorder_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IComponent m_component;

    //需要装饰的构件引用
    IComponent *m_pComponent;
};

static void Free(IComponent **ppComponent)
{
    DecoratorBlackBorder_Free(&(DecoratorBlackBorder *)(*ppComponent)->pImplicit);
    *ppComponent = NULL;
}

static void Display(IComponent *pComponent)
{
    DecoratorBlackBorder *pInst = (DecoratorBlackBorder *)pComponent->pImplicit;

    //增强构件的功能
    SetBlackBorder();

    //调用构件的原有功能
    pInst->pFld->m_pComponent->Display(pInst->pFld->m_pComponent);
}

static void SetBlackBorder()
{
    puts("为构件增加黑色边框。");
}

DecoratorBlackBorder * DecoratorBlackBorder_New(apr_pool_t * pSupPool, IComponent *pComponent)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    DecoratorBlackBorder *pInst = apr_palloc(pPool, sizeof(DecoratorBlackBorder));

    pInst->pFld = apr_palloc(pPool, sizeof(DecoratorBlackBorder_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_component.pImplicit = pInst;
    pInst->pFld->m_component.Free = Free;

    pInst->pFld->m_component.Display = Display;
    pInst->pFld->m_pComponent = pComponent;

    return pInst;
}

IComponent * DecoratorBlackBorder2IComponent(DecoratorBlackBorder * pInst)
{
    return &(pInst->pFld->m_component);
}

void DecoratorBlackBorder_Free(DecoratorBlackBorder ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
