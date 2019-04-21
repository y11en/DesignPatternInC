
#include <apr_pools.h>


#ifndef FILEWRITER_H
#define FILEWRITER_H

typedef struct FileWriter_Fld FileWriter_Fld;
typedef struct FileWriter FileWriter;

struct FileWriter
{
    FileWriter_Fld *pFld;
    void (* Write)(FileWriter *pInst, const char *pEncryptedText, const char *pFileName);
};
FileWriter *FileWriter_New(apr_pool_t *pSupPool);
void FileWriter_Free(FileWriter **ppInst);

#endif // !FILEWRITER_H
