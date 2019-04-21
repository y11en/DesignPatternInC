
#include <apr_pools.h>
#include "IFile.h"


#ifndef TEXT_FILE_H
#define TEXT_FILE_H

typedef struct TextFile_Fld TextFile_Fld;
typedef struct TextFile TextFile;

struct TextFile
{
    TextFile_Fld *pFld;
};

TextFile *TextFile_New(apr_pool_t *pSupPool, const char *const pName);
IFile *TextFile2IFile(TextFile *pInst);
void TextFile_Free(TextFile **ppInst);

#endif // !TEXT_FILE_H
