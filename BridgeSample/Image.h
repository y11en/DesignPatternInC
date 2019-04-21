
#include "ImageImp.h"

#ifndef IMAGE_H
#define IMAGE_H

typedef struct Image Image;

struct Image
{
    void *pImplicit;

    //设置桥接对象，分离出的一个维度(这个例子中，为不同的平台的图像像素矩阵的绘制方法)
    //外部负责释放桥接对象
	void (* SetImageImp)(Image *pInst, ImageImp *pImgImp);

    //分离出的另一个维度(这个例子中，为不同格式图片文件的解析方法)
	void (* ParseFile)(Image *pInst, const char *const pFileName);

    void (* Free)(Image **ppImg);
};

#endif // !IMAGE_H
