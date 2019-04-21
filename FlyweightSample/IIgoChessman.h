
#include "Coordinates.h"

#ifndef IIGOCHESSMAN_H
#define IIGOCHESSMAN_H

typedef struct IIgoChessman IIgoChessman;

struct IIgoChessman
{
    void *pImplicit;

    char *(* GetColor)(IIgoChessman *pIgoChessman, apr_pool_t *pPool);

    void (* Display)(IIgoChessman *pIgoChessman, Coordinates *pCoord);

    void (* Free)(IIgoChessman **ppIgoChessman);
};

#endif // !IIGOCHESSMAN_H
