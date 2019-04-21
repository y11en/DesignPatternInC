
#include <apr_pools.h>
#include "ICommand.h"


#ifndef BUTTON_H
#define BUTTON_H

typedef struct Button_Fld Button_Fld;
typedef struct Button Button;

struct Button
{
    Button_Fld *pFld;

    ICommand *(* GetCommand)(Button *pInst);
    void (* SetCommand)(Button *pInst, ICommand *pCommand);
    void (* Click)(Button *pInst);
};

Button *Button_New(apr_pool_t *pSupPool);
void Button_Free(Button **ppInst);

#endif // !BUTTON_H
