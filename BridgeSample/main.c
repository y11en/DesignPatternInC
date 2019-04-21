
#include <stdio.h>
#include <apr_pools.h>

#include "Image.h"
#include "BmpImage.h"
#include "GifImage.h"
#include "JpgImage.h"

#include "ImageImp.h"
#include "UnixImp.h"
#include "LinuxImp.h"
#include "WindowsImp.h"


int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;
    
    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    {//BmpImage
        //for (size_t i = 0; i < 100000; i++)
        //{
        //    Image *pImg = BmpImage2Image(BmpImage_New());
        //    ImageImp *pImgImp = UnixImp2ImageImp(UnixImp_New());

        //    pImg->SetImageImp(pImg, pImgImp);
        //    pImg->ParseFile(pImg, "Ahri.bmp");

        //    pImgImp->Free(&pImgImp);
        //    pImg->Free(&pImg);
        //}

        Image *pImg = BmpImage2Image(BmpImage_New(pMemPool));
        ImageImp *pImgImp = UnixImp2ImageImp(UnixImp_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Ahri.bmp");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    {//GifImage
        Image *pImg = GifImage2Image(GifImage_New(pMemPool));
        ImageImp *pImgImp = LinuxImp2ImageImp(LinuxImp_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Alice.gif");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    {//JpgImage
        Image *pImg = JpgImage2Image(JpgImage_New(pMemPool));
        ImageImp *pImgImp = WindowsImp2ImageImp(WindowsImp_New(pMemPool));

        pImg->SetImageImp(pImg, pImgImp);
        pImg->ParseFile(pImg, "Captured.jpg");

        pImgImp->Free(&pImgImp);
        pImg->Free(&pImg);
    }

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}