
#include <apr_pools.h>
#include "Memento.h"


#ifndef CHESSMAN_H
#define CHESSMAN_H

typedef struct Chessman_Fld Chessman_Fld;
typedef struct Chessman Chessman;

struct Chessman
{
    Chessman_Fld *pFld;

    char *(* GetLabel)(Chessman *pInst, apr_pool_t *pPool);
    void (* SetLabel)(Chessman *pInst, const char *pLabel);
    int (* GetX)(Chessman *pInst);
    void (* SetX)(Chessman *pInst, int nX);
    int (* GetY)(Chessman *pInst);
    void (* SetY)(Chessman *pInst, int nY);
    Memento *(* Save)(Chessman *pInst, apr_pool_t *pPool, Memento *pOut);
    void (* Restore)(Chessman *pInst, Memento *pMemento);
};

Chessman *Chessman_New(apr_pool_t *pSupPool, const char *pLabel, int nX, int nY);
void Chessman_Free(Chessman **ppInst);

#endif // !CHESSMAN_H
