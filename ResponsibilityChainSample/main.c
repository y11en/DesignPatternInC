
#include <stdio.h>
#include <apr_pools.h>
#include "PurchaseRequest.h"
#include "IApprover.h"
#include "Board.h"
#include "President.h"
#include "VicePresident.h"
#include "Manager.h"
#include "Director.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    //ÔðÈÎÖ÷Ìå
    IApprover *pZhangWj = Director2IApprover(Director_New(pMemPool, "ÕÅÎÞ¼É"));
    IApprover *pHuangR = Manager2IApprover(Manager_New(pMemPool, "»ÆÈØ"));
    IApprover *pYangG = VicePresident2IApprover(VicePresident_New(pMemPool, "Ñî¹ý"));
    IApprover *pGuoJ = President2IApprover(President_New(pMemPool, "¹ù¾¸"));
    IApprover *pBoard = Board2IApprover(Board_New(pMemPool, "¶­ÊÂ»á"));

    //´´½¨ÔðÈÎÁ´
    pZhangWj->SetSuccessor(pZhangWj, pHuangR);
    pHuangR->SetSuccessor(pHuangR, pYangG);
    pYangG->SetSuccessor(pYangG, pGuoJ);
    pGuoJ->SetSuccessor(pGuoJ, pBoard);

    PurchaseRequest *pReq1 = PurchaseRequest_New(pMemPool, 45000, 1001, "¹ºÂòÒÐÌì½£");
    PurchaseRequest *pReq2 = PurchaseRequest_New(pMemPool, 70000, 1002, "¹ºÂò¡¶¿û»¨±¦µä¡·");
    PurchaseRequest *pReq3 = PurchaseRequest_New(pMemPool, 90000, 1003, "¹ºÂò¡¶Ò×½î¾­¡·");
    PurchaseRequest *pReq4 = PurchaseRequest_New(pMemPool, 160000, 1004, "¹ºÂò¹Å¶­");
    PurchaseRequest *pReq5 = PurchaseRequest_New(pMemPool, 900000, 1005, "¹ºÂòÌÒ»¨µº");

    pZhangWj->ProcessRequest(pZhangWj, pReq1);
    pZhangWj->ProcessRequest(pZhangWj, pReq2);
    pZhangWj->ProcessRequest(pZhangWj, pReq3);
    pZhangWj->ProcessRequest(pZhangWj, pReq4);
    pZhangWj->ProcessRequest(pZhangWj, pReq5);

    PurchaseRequest_Free(&pReq1);
    PurchaseRequest_Free(&pReq2);
    PurchaseRequest_Free(&pReq3);
    PurchaseRequest_Free(&pReq4);
    PurchaseRequest_Free(&pReq5);

    pZhangWj->Free(&pZhangWj);
    pHuangR->Free(&pHuangR);
    pYangG->Free(&pYangG);
    pGuoJ->Free(&pGuoJ);
    pBoard->Free(&pBoard);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}