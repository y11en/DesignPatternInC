
#include "IImageImp.h"

#ifndef IIMAGE_H
#define IIMAGE_H

typedef struct IImage IImage;

struct IImage
{
    void *pImplicit;

    //设置桥接对象，分离出的一个维度(这个例子中，为不同的平台的图像像素矩阵的绘制方法)
    //外部负责释放桥接对象
	void (* SetImageImp)(IImage *pImage, IImageImp *pImageImp);

    //分离出的另一个维度(这个例子中，为不同格式图片文件的解析方法)
	void (* ParseFile)(IImage *pImage, const char *const pFileName);

    void (* Free)(IImage **ppImage);
};

#endif // !IIMAGE_H
