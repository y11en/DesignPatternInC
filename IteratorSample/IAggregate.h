
#include "IIterator.h"
#include "TxObjectRing.h"

#ifndef IAGGREGATE_H
#define IAGGREGATE_H

typedef struct IAggregate IAggregate;

struct IAggregate
{
    void *pImplicit;

    //获取内部存储对象的环
    RING(TxObject) *(* GetTxObjects)(IAggregate *pAggregate);
    //设置内部存储对象的环
    void (* SetTxObjects)(IAggregate *pAggregate, RING(TxObject) *pTxObjects);

    //创建迭代器的方法
    IIterator *(* CreateIterator)(IAggregate *pAggregate);

    void (* Free)(IAggregate **ppAggregate);
};

#endif // !IAGGREGATE_H
