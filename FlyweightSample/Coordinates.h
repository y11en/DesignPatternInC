
#include <apr_pools.h>


#ifndef COORDINATES_H
#define COORDINATES_H

typedef struct Coordinates_Fld Coordinates_Fld;
typedef struct Coordinates Coordinates;

struct Coordinates
{
    Coordinates_Fld *pFld;

    int (* GetX)(Coordinates *pInst);
    void (* SetX)(Coordinates *pInst, int x);
    int (* GetY)(Coordinates *pInst);
    void (* SetY)(Coordinates *pInst, int y);
};

Coordinates *Coordinates_New(apr_pool_t *pSupPool, int x, int y);
void Coordinates_Free(Coordinates **ppInst);

#endif // !COORDINATES_H
