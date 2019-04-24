
#include <apr_pools.h>
#include "IFile.h"


#ifndef FILEVIDEO_H
#define FILEVIDEO_H

typedef struct FileVideo_Fld FileVideo_Fld;
typedef struct FileVideo FileVideo;

struct FileVideo
{
	FileVideo_Fld *pFld;
};

FileVideo *FileVideo_New(apr_pool_t *pSupPool, const char *const pName);
IFile *FileVideo2IFile(FileVideo *pInst);
void FileVideo_Free(FileVideo **ppInst);

#endif // !FILEVIDEO_H
