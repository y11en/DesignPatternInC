
#include <apr_pools.h>
#include "IObserver.h"


#ifndef OBSERVERPLAYER_H
#define OBSERVERPLAYER_H

typedef struct ObserverPlayer_Fld ObserverPlayer_Fld;
typedef struct ObserverPlayer ObserverPlayer;

struct ObserverPlayer
{
	ObserverPlayer_Fld *pFld;
};

ObserverPlayer *ObserverPlayer_New(apr_pool_t *pSupPool, const char *pName);
IObserver *ObserverPlayer2IObserver(ObserverPlayer *pInst);
void ObserverPlayer_Free(ObserverPlayer **ppInst);

#endif // !OBSERVERPLAYER_H
