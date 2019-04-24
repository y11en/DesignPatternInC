
#include <apr_pools.h>
/*#include*/typedef struct IObserver IObserver;


#ifndef INOTIFIER_H
#define INOTIFIER_H

typedef struct INotifier INotifier;

struct INotifier
{
	void *pImplicit;

	char *(* GetAllyName)(INotifier *pNotifier, apr_pool_t *pPool);
	void (* SetAllyName)(INotifier *pNotifier, const char *pName);
	void (* Join)(INotifier *pNotifier, IObserver *pObserver);
	void (* Quit)(INotifier *pNotifier, IObserver *pObserver);
	void (* Notify)(INotifier *pNotifier, const char *pName);

	void (* Free)(INotifier **ppNotifier);
};

#endif // !INOTIFIER_H
