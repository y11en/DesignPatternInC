
#include <stdio.h>
#include "Button.h"

struct Button_Fld
{
    apr_pool_t *m_pPool;

    ICommand *m_pCmd;
};

static ICommand *GetCommand(Button *pInst)
{
    return pInst->pFld->m_pCmd;
}

static void SetCommand(Button *pInst, ICommand *pCommand)
{
    pInst->pFld->m_pCmd = pCommand;
}

static void Click(Button *pInst)
{
    puts("µ¥»÷°´Å¥¡£\n");
    pInst->pFld->m_pCmd->Execute(pInst->pFld->m_pCmd);
}

Button * Button_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    Button *pInst = apr_palloc(pPool, sizeof(Button));

    pInst->pFld = apr_palloc(pPool, sizeof(Button_Fld));
    pInst->pFld->m_pPool = pPool;

    pInst->pFld->m_pCmd = NULL;

    pInst->GetCommand = GetCommand;
    pInst->SetCommand = SetCommand;
    pInst->Click = Click;

    return pInst;
}

void Button_Free(Button ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
