﻿#include<opencv2\opencv.hpp>
#include<iostream>
#include<vector>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【线性混合示例】"
const int g_nMaxAlphaValue = 100;    //Alpha的最大值
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*) {
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//则beta值为1减去alpha值
	g_dBetaValue = (1.0 - g_dAlphaValue);

	//根据alpha和beta值进行线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	//显示效果图
	imshow(WINDOW_NAME, g_dstImage);
}
int main(int argc, char** argv) {
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");

	if (!g_srcImage1.data) {
		cout << "读取第一幅图片错误！" << endl;
		return -1;
	}
	if (!g_srcImage2.data) {
		cout << "读取第二幅图片错误！" << endl;
		return -1;
	}
	//设置滑动条初值为70
	g_nAlphaValueSlider = 70;

	namedWindow(WINDOW_NAME);

	//在创建的窗体中创建一个滑动条控件
	char TrackbarName[50];
	sprintf(TrackbarName, "透明值 %d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlider, 0);


	waitKey();
	return 0;
}