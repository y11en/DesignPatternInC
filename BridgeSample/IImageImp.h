
#include "Matrix.h"

#ifndef IMAGEIMP_H
#define IMAGEIMP_H

typedef struct IImageImp IImageImp;

//在本例子中，作为桥接对象接口
struct IImageImp
{
    //实现桥接接口的类的实例指针
	void *pImplicit;

    //作为桥接对象的业务方法，以不同格式图片解析后的图像像素矩阵为参数，
    //实现在不同平台上绘制图像像素矩阵
	void (* DoPaint)(IImageImp *pImageImp, Matrix *mat);

    //释放桥接类的实例
	void (* Free)(IImageImp **ppImageImp);
};

#endif // !IMAGEIMP_H
