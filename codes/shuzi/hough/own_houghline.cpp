//#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <string.h>
#include <map>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

//0 represent black
//1 represent white
#define LINE 0
#define ELSE 255
typedef Mat_<uchar> MatU;

double f(int xi, int yi, double theta){
    double ret=xi*cos(theta)+yi*sin(theta);
    return ret;
}

double dis(double k, double b, double xi, double yi){
    double up=fabs(k*xi-yi+b);
    double down=sqrt(k*k+1);
    return up/down;
}

int main(){

//    string path = "/home/zhanghui/codes/shuzi/hough/build/line.png";
    Mat imgOriginal;
    imgOriginal = imread("line.png");  
//	imgOriginal = imread(path);

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
//    imshow("green", imgThresholded);
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

//    imshow("orign image", srcImage);

//    imshow("bianyuanjiance", midImage);

//    imshow("XiaoGuo", dstImage);







   
    Mat imgg=imgThresholded;

    MatU img;
    cvtColor(imgg, img, CV_RGB2GRAY);
   // Mat imhough=Mat(img.rows, img.cols, img.type());

  //  bitwise_not(img, img);
    //threshold(img, img, 128, 255, THRESH_BINARY);
    int x, y;
    double theta;
    //MatU test=MatU(img.rows, img.cols, img.type());
    //Matrix test=new Matrix(img.rows, img.cols);
    //int test[img.rows*4][img.cols];
    int test[314][800];
    for(x=0; x<314; x++){
        for(y=0; y<800; y++){
            test[x][y]=0;
        }
    }

    for(y=0; y<img.rows; y++){
        for(x=0; x<img.cols; x++){
            Point cur(x,y);
            if(img(cur)==LINE){
             //   cout << "(" << i << "," << j << ")" << endl;
                for(theta=0; theta<3.14; theta=theta+0.01){
                    double rho=f(x, y, theta);
                  //  if(rho>150)   cout << rho << endl;
                    test[int(theta*100)][int(rho)+400]+=1;
                  //  数组下标非负，遭遇负数rho时要处理，所以统统加400，后面处理时再减400
                  //  test[theta][int(rho)]+=1;
                }
            }
        }
    }

    int max=-1;
    double mx=0, my=0;
    for(y=0; y<800; y++){
        for(x=0; x<314; x++){
            if(test[x][y]>max){
                max=test[x][y];
                mx=x/100.0;
                my=y-400;
            }
        }
    }
    //cout << "max=" << max << endl;
    //cout << "mx=" << mx << endl;
    double mk=-1.0/tan(mx);
    double mb=my*1.0/sin(mx);
    cout << "k=" << mk << endl << "b=" << mb << endl;

   
    double dk=1;//pivot valut

    vector<Point> store;
    double xmin=200, xmax=0;//[xmin,xmax]表示直线横坐标范围
    for(y=0; y<img.rows; y++){
        for(x=0; x<img.cols; x++){
            Point cur(x, y);
            if(img(cur)==LINE){
                if(dis(mk, mb, x, y)<dk){
                    store.push_back(Point(x, y));
                    if(xmin>x) xmin=x;
                    if(xmax<x) xmax=x;
                }
            }
        }
    }


    double A=0,//sigma of (xi*xi)
            B=0,//sigma of (xi)
            C=0,//sigma of (xi*yi)
            D=0;//sigma of (yi)
    double k2x,// k of ercheng
            b2x;//b of ercheng
    int m=store.size();
    size_t i;
    for(i=0; i<store.size(); i++){
        double tx=store[i].x;
        double ty=store[i].y;
        A+=tx*tx;
        B+=tx;
        C+=tx*ty;
        D+=ty;
    }
    k2x=(D*B-m*C)/(B*B-m*A);
    b2x=(D-B*k2x)/m;

  //  line( im2x, Point(xmin, k2x*xmin+b2x), Point(xmax, k2x*xmax+b2x), Scalar(255), 3, CV_AA);
   // line( img, Point(xmin, k2x*xmin+b2x), Point(xmax, k2x*xmax+b2x), Scalar(255), 3, CV_AA);
  //  imshow("im2x", im2x);
    imshow("imgg", imgg);
    imshow("img", img);

    Mat im2x=imgg.clone();
    cout << "xmin=" << xmin << "    xmax=" << xmax << endl;
    line( im2x, Point(xmin, k2x*xmin+b2x), Point(xmax, k2x*xmax+b2x), Scalar(255), 3, CV_AA);
   //line( im2x, Point(0, 0), Point(100, 100), Scalar(0,0,255), 3, CV_AA);
    imshow("im2x", im2x);

    waitKey();

    return 0;
}
