
#include <apr_pools.h>
#include "IFile.h"


#ifndef VIDEO_FILE_H
#define VIDEO_FILE_H

typedef struct VideoFile_Fld VideoFile_Fld;
typedef struct VideoFile VideoFile;

struct VideoFile
{
    VideoFile_Fld *pFld;
};

VideoFile *VideoFile_New(apr_pool_t *pSupPool, const char *const pName);
IFile *VideoFile2IFile(VideoFile *pInst);
void VideoFile_Free(VideoFile **ppInst);

#endif // !VIDEO_FILE_H
