
#include <apr_pools.h>


#ifndef FILEREADER_H
#define FILEREADER_H

typedef struct FileReader_Fld FileReader_Fld;
typedef struct FileReader FileReader;

struct FileReader
{
    FileReader_Fld *pFld;

    char *(* Read)(FileReader *pInst, const char *pFileName, apr_pool_t *pPool);
};

FileReader *FileReader_New(apr_pool_t *pSupPool);
void FileReader_Free(FileReader **ppInst);

#endif // !FILEREADER_H
