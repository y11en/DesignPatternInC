
#ifndef IENCRYPTFACADE_H
#define IENCRYPTFACADE_H

typedef struct IEncryptFacade IEncryptFacade;

struct IEncryptFacade
{
    void *pImplicit;

    void (* ToEncryptFile)(IEncryptFacade *pFacade, const char *pFileName, const char *pEncryptedName);

    void (* Free)(IEncryptFacade **ppFacade);
};

#endif // !IENCRYPTFACADE_H
