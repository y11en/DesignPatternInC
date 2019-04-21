
#ifndef ICHART_H
#define ICHART_H

typedef struct IChart IChart;

struct IChart
{
	//实现接口的类类型的对象指针。实际类型指针
	void *pImplicit;

	//接口的业务逻辑，约定具体的操作
	void (*Display)();

	//释放接口对应的实例
	void (* Free)(IChart **ppchart);
};

#endif // !ICHART_H
