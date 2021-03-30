#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc,char** argv)
{
    string path = "/home/zhanghui/codes/shuzi/hough/build/line.png";
    Mat imgOriginal;
// imgOriginal = imread("line.png");  
	imgOriginal = imread(path);

    Mat imgHSV, imgBGR;
    Mat imgThresholded;

    vector<Mat> hsvSplit;   //创建向量容器，存放HSV的三通道数据
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
    split(imgHSV, hsvSplit);			//分类原图像的HSV三通道
    equalizeHist(hsvSplit[2], hsvSplit[2]);    //对HSV的亮度通道进行直方图均衡
    merge(hsvSplit, imgHSV);				   //合并三种通道
    cvtColor(imgHSV, imgBGR, COLOR_HSV2BGR);    //将HSV空间转回至RGB空间，为接下来的颜色识别做准备

    imgBGR = imgOriginal.clone();
    inRange(imgBGR, Scalar(0, 128, 0), Scalar(127, 255, 127), imgThresholded); //绿色
    imshow("green", imgThresholded);
    imshow("Original", imgOriginal); //show the original image



    Mat srcImage = imgThresholded;
    // Mat srcImage = imread(argv[1]);
    Mat midImage, dstImage;

    Canny(srcImage, midImage, 50, 200, 3);
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

    vector<Vec4i> lines;
    HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
    }

    imshow("orign image", srcImage);

    imshow("bianyuanjiance", midImage);

    imshow("XiaoGuo", dstImage);

    waitKey(0);

    return 0;
}

