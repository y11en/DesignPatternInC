
#include <apr_pools.h>
#include "ICommand.h"


#ifndef COMMANDHELP_H
#define COMMANDHELP_H

typedef struct CommandHelp_Fld CommandHelp_Fld;
typedef struct CommandHelp CommandHelp;

struct CommandHelp
{
    CommandHelp_Fld *pFld;
};

CommandHelp *CommandHelp_New(apr_pool_t *pSupPool);
ICommand *CommandHelp2ICommand(CommandHelp *pInst);
void CommandHelp_Free(CommandHelp **ppInst);

#endif // !COMMANDHELP_H
