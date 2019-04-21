
#include <stdbool.h>
#include "TxObjectRing.h"

#ifndef IITERATOR_H
#define IITERATOR_H

typedef struct IIterator IIterator;

struct IIterator
{
    void *pImplicit;

    //移至下一个
    void (* Next)(IIterator *pIterator);
    //是否为最后一个
    bool (* IsLast)(IIterator *pIterator);
    //移至前一个
    void (* Previous)(IIterator *pIterator);
    //是否为第一个
    bool (* IsFirst)(IIterator *pIterator);
    //获取下一个元素
    TxObject *(* GetNextItem)(IIterator *pIterator);
    //获取前一个元素
    TxObject *(* GetPreviousItem)(IIterator *pIterator);

    void (* Free)(IIterator **ppIterator);
};

#endif // !IITERATOR_H
