
#include "DisplayHelp.h"
#include "CommandHelp.h"

struct CommandHelp_Fld
{
    apr_pool_t *m_pPool;

    ICommand m_command;

    //ÃüÁî½ÓÊÕ·½
    DisplayHelp *m_pReceiver;
};

static void Free(ICommand **ppCommand)
{
    CommandHelp_Free(&(CommandHelp *)(*ppCommand)->pImplicit);
    *ppCommand = NULL;
}

static void Execute(ICommand *pCommand)
{
    CommandHelp *pInst = (CommandHelp *)pCommand->pImplicit;
    pInst->pFld->m_pReceiver->Display(pInst->pFld->m_pReceiver);
}

CommandHelp * CommandHelp_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    CommandHelp *pInst = apr_palloc(pPool, sizeof(CommandHelp));
    
    pInst->pFld = apr_palloc(pPool, sizeof(CommandHelp_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_command.pImplicit = pInst;
    pInst->pFld->m_command.Free = Free;

    pInst->pFld->m_command.Execute = Execute;

    pInst->pFld->m_pReceiver = DisplayHelp_New(pInst->pFld->m_pPool);

    return pInst;
}

ICommand * CommandHelp2ICommand(CommandHelp * pInst)
{
    return &(pInst->pFld->m_command);
}

void CommandHelp_Free(CommandHelp ** ppInst)
{
    DisplayHelp_Free(&((*ppInst)->pFld->m_pReceiver));

    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
