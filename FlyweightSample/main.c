
#include <stdlib.h>
#include <stdio.h>
#include <apr_pools.h>
#include "Coordinates.h"
#include "IIgoChessman.h"
#include "IgoChessmanFactory.h"


//int nTimes = 3000;
//int nCount = 0;
//
//int main(int argc, char **argv)
//{
//    apr_pool_t *pMemPool;
//
//    apr_initialize();
//    
//    apr_pool_create(&pMemPool, NULL);
//
//    IIgoChessman *pBlack1, *pBlack2, *pBlack3;
//    IIgoChessman *pWhite1, *pWhite2;
//    IgoChessmanFactory *pFactory;
//
//    pFactory = GetIgoChessmanFactoryInstance(pMemPool);
//
//    pBlack1 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);
//    pBlack2 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);
//    pBlack3 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);
//
//    printf("黑子1和黑子2 %s 相同的。\n", (pBlack1 == pBlack2 ? "是" : "不是"));
//
//    pWhite1 = pFactory->GetIgoChessman(pFactory, COLOR_WHITE);
//    pWhite2 = pFactory->GetIgoChessman(pFactory, COLOR_WHITE);
//    printf("白子1和白子2 %s 相同的。\n", (pWhite1 == pWhite2 ? "是" : "不是"));
//
//    Coordinates *pCoord1 = Coordinates_New(pMemPool, 1, 2);
//    Coordinates *pCoord2 = Coordinates_New(pMemPool, 3, 4);
//    Coordinates *pCoord3 = Coordinates_New(pMemPool, 1, 3);
//    Coordinates *pCoord4 = Coordinates_New(pMemPool, 2, 5);
//    Coordinates *pCoord5 = Coordinates_New(pMemPool, 2, 4);
//    pBlack1->Display(pBlack1, pCoord1);
//    pBlack2->Display(pBlack2, pCoord2);
//    pBlack3->Display(pBlack3, pCoord3);
//    pWhite1->Display(pWhite1, pCoord4);
//    pWhite2->Display(pWhite1, pCoord5);
//
//    Coordinates_Free(&pCoord1);
//    Coordinates_Free(&pCoord2);
//    Coordinates_Free(&pCoord3);
//    Coordinates_Free(&pCoord4);
//    Coordinates_Free(&pCoord5);
//
//    IgoChessmanFactory_Free(&pFactory);
//
//    apr_pool_destroy(pMemPool);
//
//    apr_terminate();
//
//    return ++nCount < nTimes ? main(0, NULL) : EXIT_SUCCESS;
//}


int main(int argc, char **argv)
{
    for (size_t i = 0; i < 5000; i++)
    {
        apr_pool_t *pMemPool;

        apr_initialize();

        apr_pool_create(&pMemPool, NULL);

        IIgoChessman *pBlack1, *pBlack2, *pBlack3;
        IIgoChessman *pWhite1, *pWhite2;
        IgoChessmanFactory *pFactory;

        pFactory = GetIgoChessmanFactoryInstance(pMemPool);

        pBlack1 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);
        pBlack2 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);
        pBlack3 = pFactory->GetIgoChessman(pFactory, COLOR_BLACK);

        printf("黑子1和黑子2 %s 相同的。\n", (pBlack1 == pBlack2 ? "是" : "不是"));

        pWhite1 = pFactory->GetIgoChessman(pFactory, COLOR_WHITE);
        pWhite2 = pFactory->GetIgoChessman(pFactory, COLOR_WHITE);
        printf("白子1和白子2 %s 相同的。\n", (pWhite1 == pWhite2 ? "是" : "不是"));

        Coordinates *pCoord1 = Coordinates_New(pMemPool, 1, 2);
        Coordinates *pCoord2 = Coordinates_New(pMemPool, 3, 4);
        Coordinates *pCoord3 = Coordinates_New(pMemPool, 1, 3);
        Coordinates *pCoord4 = Coordinates_New(pMemPool, 2, 5);
        Coordinates *pCoord5 = Coordinates_New(pMemPool, 2, 4);
        pBlack1->Display(pBlack1, pCoord1);
        pBlack2->Display(pBlack2, pCoord2);
        pBlack3->Display(pBlack3, pCoord3);
        pWhite1->Display(pWhite1, pCoord4);
        pWhite2->Display(pWhite1, pCoord5);

        Coordinates_Free(&pCoord1);
        Coordinates_Free(&pCoord2);
        Coordinates_Free(&pCoord3);
        Coordinates_Free(&pCoord4);
        Coordinates_Free(&pCoord5);

        IgoChessmanFactory_Free(&pFactory);

        apr_pool_destroy(pMemPool);

        apr_terminate();
    }

    return EXIT_SUCCESS;
}