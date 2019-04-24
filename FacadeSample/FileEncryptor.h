
#include <apr_pools.h>


#ifndef FILEENCRYPTOR_H
#define FILEENCRYPTOR_H

typedef struct FileEncryptor_Fld FileEncryptor_Fld;
typedef struct FileEncryptor FileEncryptor;

struct FileEncryptor
{
	FileEncryptor_Fld *pFld;

    char *(* Encrypt)(FileEncryptor *pInst, const char *pPlainText, apr_pool_t *pPool);
};

FileEncryptor *FileEncryptor_New(apr_pool_t *pSupPool);
void FileEncryptor_Free(FileEncryptor **ppInst);

#endif // !FILEENCRYPTOR_H
