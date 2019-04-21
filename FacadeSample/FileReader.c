
#include <stdio.h>
#include "FileReader.h"

//属性、方法声明

struct FileReader_Fld
{
    apr_pool_t *m_pPool;
};

char *Read(FileReader *pInst, const char *pFileName, apr_pool_t *pPool)
{
    puts("读取文件，获取明文。");

    FILE *pFile = fopen(pFileName, "r");
    if (pFile)
    {
        long len = -1;
        {
            fseek(pFile, 0L, SEEK_END);
            len = ftell(pFile);
            fseek(pFile, 0L, SEEK_SET);
        }

        int nIndex = 0;
        char *pRead = apr_palloc(pPool, sizeof(char) * len + 1/* '\0' */);
        while ((*(pRead + nIndex++) = getc(pFile)) != EOF) putc(*(pRead + nIndex - 1), stdout);
        *(pRead + nIndex) = '\0';

        puts("");

        fclose(pFile);

        return pRead;
    }
    else
    {
        puts("打开文件失败。");
        return NULL;
    }
}

FileReader * FileReader_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    FileReader *pInst = apr_palloc(pPool, sizeof(FileReader));
    
    pInst->pFld = apr_palloc(pPool, sizeof(FileReader_Fld));
    pInst->pFld->m_pPool = pPool;
    
    pInst->Read = Read;

    return pInst;
}

void FileReader_Free(FileReader **ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
