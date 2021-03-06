// gray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	Mat img = imread("C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170915_171540.jpg");
	Mat grey;
	cvtColor(img, grey, COLOR_BGR2GRAY);

	Mat sobelx,sobely,dst;
	/*Sobel(grey, sobelx, CV_32F, 1, 0);
	Sobel(grey, sobely, CV_32F, 0, 1);*/
	//对两个方向上的图像进行求梯度
	spatialGradient(grey, sobelx, sobely);
	

	double minVal, maxVal;
	minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	Mat drawx;
	//对灰阶图像进行编码，颜色范围一样，但是将零头去掉
	sobelx.convertTo(drawx, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
	minMaxLoc(sobely, &minVal, &maxVal); //find minimum and maximum intensities
	Mat drawy;
	sobely.convertTo(drawy, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

	addWeighted(sobelx, 0.5, sobely, 0.5, 0.0, dst);
	namedWindow("imagex", WINDOW_NORMAL);
	namedWindow("imagey", WINDOW_NORMAL);
	namedWindow("compl", WINDOW_NORMAL);
	imshow("imagex", drawx);
	imshow("imagey", drawy);
	//为什么合成的图片是一片空白全是一样的值？
	imshow("compl", dst);
	cout << "draw'size is:" << drawx.size << endl << endl;
	cout << "drawy'size is:" << drawy.size << endl<<endl;
	waitKey();
    return 0;
}

