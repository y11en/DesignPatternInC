
#ifndef IFILE_H
#define IFILE_H

typedef struct IFile IFile;

struct IFile
{
	void *pImplicit;

    /* 
     * 添加，只是把一个IFile添加到当前IFile中，
     * 并没有包含关系，只是一种组织关系，
     * 因此，只是添加引用。
     * 当然可以按需要，将IFile的实例和引用都添加
     * 只是需要另外一种代码实现而已. */
	void (* Add)(IFile *pFile, IFile *pAdd);

    /*
     * 跟添加类似，移除只是解除这种组织关系而已，
     * 并没有销毁对象 */
	void (* Remove)(IFile *pFile, IFile *pRmv);

    /* 
     * 获取子文件指针。
     * 索引为C-Style，从0开始 */
	IFile *(* GetChild)(IFile *pFile, int nIndex);

    /* 依赖于业务逻辑的方法，这里模拟一个杀毒功能 */
	void (* KillVirus)(IFile *pFile);

	void (* Free)(IFile **ppFile);
};

#endif // !IFILE_H
