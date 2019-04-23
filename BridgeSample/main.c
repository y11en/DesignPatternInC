
#include <stdio.h>
#include <apr_pools.h>

#include "IImage.h"
#include "ImageBmp.h"
#include "ImageGif.h"
#include "ImageJpg.h"

#include "IImageImp.h"
#include "ImageImpUnix.h"
#include "ImageImpLinux.h"
#include "ImageImpWindows.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;
    
    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    {//ImageBmp
        //for (size_t i = 0; i < 100000; i++)
        //{
        //    IImage *pImg = ImageBmp2IImage(ImageBmp_New());
        //    IImageImp *pImgImp = ImageImpUnix2IImageImp(ImageImpUnix_New());

        //    pImg->SetImageImp(pImg, pImgImp);
        //    pImg->ParseFile(pImg, "Ahri.bmp");

        //    pImgImp->Free(&pImgImp);
        //    pImg->Free(&pImg);
        //}

        IImage *pImg = ImageBmp2IImage(ImageBmp_New(pMemPool));
        IImageImp *pImgImp = ImageImpUnix2IImageImp(ImageImpUnix_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Ahri.bmp");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    {//ImageGif
        IImage *pImg = ImageGif2IImage(ImageGif_New(pMemPool));
        IImageImp *pImgImp = ImageImpLinux2IImageImp(ImageImpLinux_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Alice.gif");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    {//ImageJpg
        IImage *pImg = ImageJpg2IImage(ImageJpg_New(pMemPool));
        IImageImp *pImgImp = ImageImpWindows2IImageImp(ImageImpWindows_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Captured.jpg");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}