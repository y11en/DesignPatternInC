
#include <stdio.h>
#include <apr_pools.h>
#include "Button.h"
#include "ICommand.h"
#include "CommandHelp.h"
#include "CommandExit.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    Button *pBtn = Button_New(pMemPool);

    ICommand *pCmd = CommandHelp2ICommand(CommandHelp_New(pMemPool));
    pBtn->SetCommand(pBtn, pCmd);
    pBtn->Click(pBtn);
    pCmd->Free(&pCmd);

    ICommand *pCmd2 = CommandExit2ICommand(CommandExit_New(pMemPool));
    pBtn->SetCommand(pBtn, pCmd2);
    pBtn->Click(pBtn);
    pCmd2->Free(&pCmd2);

    Button_Free(&pBtn);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}