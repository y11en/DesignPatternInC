
#include <apr_pools.h>
/*#include*/typedef struct INotifier INotifier;


#ifndef IOBSERVER_H
#define IOBSERVER_H

typedef struct IObserver IObserver;

struct IObserver
{
	void *pImplicit;

	char *(* GetName)(IObserver *pObserver, apr_pool_t *pPool);
	void (* SetName)(IObserver *pObserver, const char *pName);
	void (* Help)(IObserver *pObserver);
	void (* BeAttacked)(IObserver *pObserver, INotifier *pNotifier);

	void (* Free)(IObserver **ppObserver);
};

#endif // !IOBSERVER_H
