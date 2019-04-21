
#include <stdio.h>
#include <apr_pools.h>
#include "IComponent.h"
#include "ComponentWindow.h"
#include "DecoratorScrollBar.h"
#include "DecoratorBlackBorder.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;
    
    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    IComponent *pComponent = ComponentWindow2IComponent(ComponentWindow_New(pMemPool));//具体类型定义，抽象构件声明
    IComponent *pDecorator = DecoratorScrollBar2IComponent(DecoratorScrollBar_New(pMemPool, pComponent));//定义透明装饰器并对构件进行装饰
    IComponent *pDecorator2 = DecoratorBlackBorder2IComponent(DecoratorBlackBorder_New(pMemPool, pDecorator));//再次对构件进行装饰

    pDecorator2->Display(pDecorator2);
    
    pDecorator2->Free(&pDecorator2);
    pDecorator->Free(&pDecorator);
    pComponent->Free(&pComponent);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}
