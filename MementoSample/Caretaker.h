
#include <apr_pools.h>
#include "Memento.h"


#ifndef CARETAKER_H
#define CARETAKER_H

typedef struct Caretaker_Fld Caretaker_Fld;
typedef struct Caretaker Caretaker;

struct Caretaker
{
    Caretaker_Fld *pFld;

    Memento *(* GetMemento)(Caretaker *pInst);
    void (* SetMemento)(Caretaker *pInst, Memento *pMemento);
};

Caretaker *Caretaker_New(apr_pool_t *pSupPool);
void Caretaker_Free(Caretaker **ppInst);

#endif // !CARETAKER_H
