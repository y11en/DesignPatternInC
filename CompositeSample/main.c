
#include <stdio.h>
#include <apr_pools.h>
#include "IFile.h"
#include "FileFolder.h"
#include "FileImage.h"
#include "FileText.h"
#include "FileVideo.h"

int main(int argc, char **argv)
{
    apr_pool_t *pMemPool;

    apr_initialize();

    apr_pool_create(&pMemPool, NULL);

    IFile *pFile1, *pFile2, *pFile3, *pFile4, *pFile5;
    IFile *pFolder1, *pFolder2, *pFolder3, *pFolder4;

    pFolder1 = FileFolder2IFile(FileFolder_New(pMemPool, "我的资料"));
    pFolder2 = FileFolder2IFile(FileFolder_New(pMemPool, "图像文件夹"));
    pFolder3 = FileFolder2IFile(FileFolder_New(pMemPool, "文本文件夹"));
    pFolder4 = FileFolder2IFile(FileFolder_New(pMemPool, "视频文件夹"));

    pFile1 = FileImage2IFile(FileImage_New(pMemPool, "小龙女.jpg"));
    pFile2 = FileImage2IFile(FileImage_New(pMemPool, "张无忌.gif"));
    pFile3 = FileText2IFile(FileText_New(pMemPool, "九阴真经.txt"));
    pFile4 = FileText2IFile(FileText_New(pMemPool, "葵花宝典.doc"));
    pFile5 = FileVideo2IFile(FileVideo_New(pMemPool, "神雕侠侣.rmvb"));

    pFolder2->Add(pFolder2, pFile1);
    pFolder2->Add(pFolder2, pFile2);
    pFolder3->Add(pFolder3, pFile3);
    pFolder3->Add(pFolder3, pFile4);
    pFolder4->Add(pFolder4, pFile5);
    pFolder1->Add(pFolder1, pFolder2);
    pFolder1->Add(pFolder1, pFolder3);
    pFolder1->Add(pFolder1, pFolder4);

    //从“我的资料”节点开始进行杀毒操作
    pFolder1->KillVirus(pFolder1);

    apr_pool_destroy(pMemPool);

    apr_terminate();

    return EXIT_SUCCESS;
}