#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#define PI 3.1415926
 
using namespace cv;
using namespace std;
 
void RGB2HSV(double red, double green, double blue, double& hue, double& saturation, double& intensity)
{
	 
	double r, g, b;
	double h, s, i;
 
	double sum;
	double minRGB, maxRGB;
	double theta;
 
	r = red / 255.0;
	g = green / 255.0;
	b = blue / 255.0;
 
	minRGB = ((r<g) ? (r) : (g));
	minRGB = (minRGB<b) ? (minRGB) : (b);
 
	maxRGB = ((r>g) ? (r) : (g));
	maxRGB = (maxRGB>b) ? (maxRGB) : (b);
 
	sum = r + g + b;
	i = sum / 3.0;
 
	if (i<0.001 || maxRGB - minRGB<0.001)
	{
		h = 0.0;
		s = 0.0;
	}
	else
	{
		s = 1.0 - 3.0*minRGB / sum;
		theta = sqrt((r - g)*(r - g) + (r - b)*(g - b));
		theta = acos((r - g + r - b)*0.5 / theta);
		if (b <= g)
			h = theta;
		else
			h = 2 * PI - theta;
		if (s <= 0.01)
			h = 0;
	}
 
	hue = (int)(h * 180 / PI);
	saturation = (int)(s * 100);
	intensity = (int)(i * 100);
}
 
Mat picture_red(Mat input)
{
	
	Mat frame;
	Mat srcImg = input;
	frame = srcImg;
	waitKey(1);
	int width = srcImg.cols;
	int height = srcImg.rows;
 
	int x, y;
	double B = 0.0, G = 0.0, R = 0.0, H = 0.0, S = 0.0, V = 0.0;
	Mat vec_rgb = Mat::zeros(srcImg.size(), CV_8UC1); //zeors生成图片和输入图片大小0矩阵
	
	for (x = 0; x < height; x++)
	{
		for (y = 0; y < width; y++)
		{
			B = srcImg.at<Vec3b>(x, y)[0];
			G = srcImg.at<Vec3b>(x, y)[1];
			R = srcImg.at<Vec3b>(x, y)[2];
			RGB2HSV(R, G, B, H, S, V);
			//红色范围，范围参考的网上。可以自己调
//			if ((H >= 312 && H <= 360) && (S >= 17 && S <= 100) && (V>18 && V < 100))
			if ((H >= 0 && H <= 180) && (S >= 0 && S <= 255) && (V>0 && V < 46))
				vec_rgb.at<uchar>(x, y) = 255;
			/*cout << H << "," << S << "," << V << endl;*/
		}
	}
	/*imshow("hsv", vec_rgb);*/
	return vec_rgb;
	
 
}
 
void O_x1y1(Mat in, double *x1, double *y1, double *x2, double *y2)
 
{
	Mat matSrc = in;
	/*Mat matSrc = imread("qwer9.png", 0);*/
 
	GaussianBlur(matSrc, matSrc, Size(5, 5), 0);//高斯滤波，除噪点
 
	vector<vector<Point> > contours;//contours的类型，双重的vector
 
	vector<Vec4i> hierarchy;//Vec4i是指每一个vector元素中有四个int型数据。
 
	//阈值
 
	threshold(matSrc, matSrc, 100, 255, THRESH_BINARY);//图像二值化
 
	//寻找轮廓，这里注意，findContours的输入参数要求是二值图像，二值图像的来源大致有两种，第一种用threshold，第二种用canny
 
	findContours(matSrc.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
 
	/// 计算矩
 
	vector<Moments> mu(contours.size());
 
	for (int i = 0; i < contours.size(); i++)
 
	{
 
		mu[i] = moments(contours[i], false);
 
	}
 
	///  计算矩中心:
 
	vector<Point2f> mc(contours.size());
 
	for (int i = 0; i < contours.size(); i++)
 
	{
 
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
 
	}
 
	/// 绘制轮廓
 
	Mat drawing = Mat::zeros(matSrc.size(), CV_8UC1);
 
	for (int i = 0; i < contours.size(); i++)
 
	{
 
		Scalar color = Scalar(255);
 
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());//绘制轮廓函数
 
		circle(drawing, mc[i], 4, color, -1, 8, 0);
		
		
	}
	*x1 = mc[0].x;
	*y1 = mc[0].y;
	*x2 = mc[contours.size()-1].x;
	*y2 = mc[contours.size() - 1].y;
	
	imshow("outImage", drawing);
	
	
 
}
 
int main()
{
	
	double xx1, yy1, xx2, yy2;
	double x1, y1, x2, y2;
 
	Mat matSrc = imread("test.png");
 
	Mat middle = picture_red(matSrc);
	O_x1y1(middle, &xx1, &yy1, &xx2, &yy2);
	x1 = xx1;
	y1 = yy1;
	x2 = xx2;
	y2 = yy2;
 
	imshow("orginImage", matSrc);
	imshow("red", picture_red(matSrc));
 
 	// rectangle(matSrc, Point(x1,y1), Point(x2,y2),Scalar(255, 0, 0), 1, LINE_8, 0);//, color, thickness=None, lineType=None, shift=None);
 	// imshow("kuang",matSrc);
	cout << "红点：" << x1 << "， " << y1 << "; " << "红点1：" << x2 << "， " << y2 << endl;
	waitKey();
 
	return 0;
}
