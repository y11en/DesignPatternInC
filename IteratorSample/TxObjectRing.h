
#include <apr_ring_ext.h>


#ifndef TXOBJECTRING_H
#define TXOBJECTRING_H

//定义void类型为object类型，
//不过这里只是临时定义的object类型，
//因此，加个前缀Tx
typedef void TxObject;

//泛型实例化得到的具体类型环链表定义
//用于聚合类，也就是IAggregate接口的实现类 内部存储对象引用
GENERIC_RING(TxObject)

#endif // !TXOBJECTRING_H
