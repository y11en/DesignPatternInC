
#include <apr_pools.h>
#include "IIgoChessman.h"


#ifndef IGOCHESSMANBLACK_H
#define IGOCHESSMANBLACK_H

typedef struct IgoChessmanBlack_Fld IgoChessmanBlack_Fld;
typedef struct IgoChessmanBlack IgoChessmanBlack;

struct IgoChessmanBlack
{
    IgoChessmanBlack_Fld *pFld;

    //继承接口，通过接口调用，
    //因此不声明接口的方法
};

IgoChessmanBlack *IgoChessmanBlack_New(apr_pool_t *pSupPool);
IIgoChessman *IgoChessmanBlack2IIgoChessman(IgoChessmanBlack *pInst);
void IgoChessmanBlack_Free(IgoChessmanBlack **ppInst);

#endif // !IGOCHESSMANBLACK_H
