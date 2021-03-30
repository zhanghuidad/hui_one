#include <opencv2/opencv.hpp> 
#include <iostream> 
using namespace cv;
 
Mat src, dst;                   // 全局变量
int element_size = 3;      //全局变量
int max_size = 21;           // 全局变量
 
void CallBack_func(int, void*);
int main(int argc, char** argv)
{
	src = imread(argv[1]);
	if (src.empty()) 
	{
		printf("could not load the  image...\n");
		return -1;
	}
	namedWindow("原图：", CV_WINDOW_AUTOSIZE);
	imshow("原图：", src);
	namedWindow("膨胀操作后：", CV_WINDOW_AUTOSIZE);
	createTrackbar("结构元尺寸 ：", "膨胀操作后：", &element_size, max_size, CallBack_func);        
	CallBack_func(element_size, 0);
 
	waitKey(0);
	return 0;
}
 
 
void CallBack_func(int, void*) 
{
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));      //创建结构元
	erode(src, dst, structureElement);               //调用腐蚀API
	imshow("膨胀操作后：", dst);
}
 
 
 
 
