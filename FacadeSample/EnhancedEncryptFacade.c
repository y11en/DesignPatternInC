
#include "EnhancedEncryptFacade.h"
#include "FileReader.h"
#include "CipherMachine.h"
#include "FileWriter.h"

//属性、方法声明

struct EnhancedEncryptFacade_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IEncryptFacade m_encryptFacade;

    FileReader *m_pReader;
    CipherMachine *m_pCipher;
    FileWriter *m_pWriter;
};

static void Free(IEncryptFacade **ppFacade)
{
    EnhancedEncryptFacade_Free(&(EnhancedEncryptFacade *)(*ppFacade)->pImplicit);
    *ppFacade = NULL;
}

static void ToEncryptFile(IEncryptFacade *pFacade, const char *pFileName, const char *pEncryptedName)
{
    EnhancedEncryptFacade *pInst = (EnhancedEncryptFacade *)pFacade->pImplicit;

    char *pPlainText = pInst->pFld->m_pReader->Read(pInst->pFld->m_pReader, pFileName, pInst->pFld->m_pPool);
    if (pPlainText)
    {
        char *pEncryptedText = pInst->pFld->m_pCipher->Encrypt(pInst->pFld->m_pCipher, pPlainText, pInst->pFld->m_pPool);
        pInst->pFld->m_pWriter->Write(pInst->pFld->m_pWriter, pEncryptedText, pEncryptedName);

        puts("\n文件加密完成..");
    }
}

EnhancedEncryptFacade * EnhancedEncryptFacade_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

    EnhancedEncryptFacade *pInst = apr_palloc(pPool, sizeof(EnhancedEncryptFacade));

    pInst->pFld = apr_palloc(pPool, sizeof(EnhancedEncryptFacade_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_encryptFacade.pImplicit = pInst;
    pInst->pFld->m_encryptFacade.Free = Free;

    pInst->pFld->m_encryptFacade.ToEncryptFile = ToEncryptFile;
    pInst->pFld->m_pReader = FileReader_New(pInst->pFld->m_pPool);
    pInst->pFld->m_pCipher = CipherMachine_New(pInst->pFld->m_pPool);
    pInst->pFld->m_pWriter = FileWriter_New(pInst->pFld->m_pPool);

    return pInst;
}

IEncryptFacade * EnhancedEncryptFacade2IEncryptFacade(EnhancedEncryptFacade * pInst)
{
    return &(pInst->pFld->m_encryptFacade);
}

void EnhancedEncryptFacade_Free(EnhancedEncryptFacade ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
