
#include <apr_pools.h>
#include "IApprover.h"


#ifndef BOARD_H
#define BOARD_H

typedef struct Board_Fld Board_Fld;
typedef struct Board Board;

struct Board
{
    Board_Fld *pFld;

    //¼Ì³Ð½Ó¿Ú
};

Board *Board_New(apr_pool_t *pSupPool, const char *pName);
IApprover *Board2IApprover(Board *pInst);
void Board_Free(Board **ppInst);

#endif // !BOARD_H

