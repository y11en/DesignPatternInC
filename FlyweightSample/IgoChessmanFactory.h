
#include <apr_pools.h>
#include "IIgoChessman.h"


#ifndef COLORTYPE_H
#define COLORTYPE_H

typedef enum ColorType ColorType;

enum ColorType
{
    COLOR_NULL = 0,
    COLOR_BLACK = 1,
    COLOR_WHITE = 2
};

#endif // !COLORTYPE_H


#ifndef IGOCHESSMANFACTORY_H
#define IGOCHESSMANFACTORY_H

typedef struct IgoChessmanFactory_Fld IgoChessmanFactory_Fld;
typedef struct IgoChessmanFactory IgoChessmanFactory;

struct IgoChessmanFactory
{
    IgoChessmanFactory_Fld *pFld;

    IIgoChessman *(* GetIgoChessman)(IgoChessmanFactory *pInst, ColorType color);
};

//IgoChessmanFactory *IgoChessmanFactory_New(apr_pool_t *pSupPool);
IgoChessmanFactory *GetIgoChessmanFactoryInstance(apr_pool_t *pSupPool);
void IgoChessmanFactory_Free(IgoChessmanFactory **ppInst);

#endif // !IGOCHESSMANFACTORY_H
