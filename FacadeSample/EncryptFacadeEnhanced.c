
#include "EncryptFacadeEnhanced.h"
#include "FileReader.h"
#include "FileEncryptor.h"
#include "FileWriter.h"

//属性、方法声明

struct EncryptFacadeEnhanced_Fld
{
    apr_pool_t *m_pPool;

    //继承接口
    IEncryptFacade m_encryptFacade;

    FileReader *m_pReader;
	FileEncryptor *m_pEncryptor;
    FileWriter *m_pWriter;
};

static void Free(IEncryptFacade **ppFacade)
{
	EncryptFacadeEnhanced_Free(&(EncryptFacadeEnhanced *)(*ppFacade)->pImplicit);
    *ppFacade = NULL;
}

static void ToEncryptFile(IEncryptFacade *pFacade, const char *pFileName, const char *pEncryptedName)
{
	EncryptFacadeEnhanced *pInst = (EncryptFacadeEnhanced *)pFacade->pImplicit;

    char *pPlainText = pInst->pFld->m_pReader->Read(pInst->pFld->m_pReader, pFileName, pInst->pFld->m_pPool);
    if (pPlainText)
    {
        char *pEncryptedText = pInst->pFld->m_pEncryptor->Encrypt(pInst->pFld->m_pEncryptor, pPlainText, pInst->pFld->m_pPool);
        pInst->pFld->m_pWriter->Write(pInst->pFld->m_pWriter, pEncryptedText, pEncryptedName);

        puts("\n文件加密完成..");
    }
}

EncryptFacadeEnhanced * EncryptFacadeEnhanced_New(apr_pool_t * pSupPool)
{
    apr_pool_t *pPool;
    apr_pool_create(&pPool, pSupPool);

	EncryptFacadeEnhanced *pInst = apr_palloc(pPool, sizeof(EncryptFacadeEnhanced));

    pInst->pFld = apr_palloc(pPool, sizeof(EncryptFacadeEnhanced_Fld));
    pInst->pFld->m_pPool = pPool;
    pInst->pFld->m_encryptFacade.pImplicit = pInst;
    pInst->pFld->m_encryptFacade.Free = Free;

    pInst->pFld->m_encryptFacade.ToEncryptFile = ToEncryptFile;
    pInst->pFld->m_pReader = FileReader_New(pInst->pFld->m_pPool);
    pInst->pFld->m_pEncryptor = FileEncryptor_New(pInst->pFld->m_pPool);
    pInst->pFld->m_pWriter = FileWriter_New(pInst->pFld->m_pPool);

    return pInst;
}

IEncryptFacade * EncryptFacadeEnhanced2IEncryptFacade(EncryptFacadeEnhanced * pInst)
{
    return &(pInst->pFld->m_encryptFacade);
}

void EncryptFacadeEnhanced_Free(EncryptFacadeEnhanced ** ppInst)
{
    apr_pool_destroy((*ppInst)->pFld->m_pPool);
    *ppInst = NULL;
}
