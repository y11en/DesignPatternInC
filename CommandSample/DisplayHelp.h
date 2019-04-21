
#include <apr_pools.h>


#ifndef DISPLAYHELP_H
#define DISPLAYHELP_H

typedef struct DisplayHelp_Fld DisplayHelp_Fld;
typedef struct DisplayHelp DisplayHelp;

struct DisplayHelp
{
    DisplayHelp_Fld *pFld;

    void (* Display)(DisplayHelp *pInst);
};

DisplayHelp *DisplayHelp_New(apr_pool_t *pSupPool);
void DisplayHelp_Free(DisplayHelp **ppInst);

#endif // !DISPLAYHELP_H
