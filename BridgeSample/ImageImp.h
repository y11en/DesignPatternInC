
#include "Matrix.h"

#ifndef IMAGEIMP_H
#define IMAGEIMP_H

typedef struct ImageImp ImageImp;

//在本例子中，作为桥接对象接口
struct ImageImp
{
    //实现桥接接口的类的实例指针
	void *pImplicit;

    //作为桥接对象的业务方法，以不同格式图片解析后的图像像素矩阵为参数，
    //实现在不同平台上绘制图像像素矩阵
	void (* DoPaint)(ImageImp *pInst, Matrix *mat);

    //释放桥接类的实例
	void (* Free)(ImageImp **ppImgImp);
};

#endif // !IMAGEIMP_H
