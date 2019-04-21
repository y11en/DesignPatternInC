
#include <apr_pools.h>


#ifndef MEMENTO_H
#define MEMENTO_H

typedef struct Memento_Fld Memento_Fld;
typedef struct Memento Memento;

struct Memento
{
    Memento_Fld *pFld;

    char *(* GetLabel)(Memento *pInst, apr_pool_t *pPool);
    void (* SetLabel)(Memento *pInst, const char *pLabel);
    int (* GetX)(Memento *pInst);
    void (* SetX)(Memento *pInst, int nX);
    int (* GetY)(Memento *pInst);
    void (* SetY)(Memento *pInst, int nY);
};

Memento *Memento_New(apr_pool_t *pSupPool, const char *pLabel, int nX, int nY);
void Memento_Free(Memento **ppInst);

#endif // !MEMENTO_H
