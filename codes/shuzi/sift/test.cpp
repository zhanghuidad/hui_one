#include <stdio.h>  
#include <iostream>  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <opencv2/legacy/legacy.hpp>
#include "opencv2/nonfree/features2d.hpp"   //SurfFeatureDetector实际在该头文件中  
// #include "opencv2/features2d.hpp"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat src = imread("a.jpg", 1);
    Mat src2 = imread("b.jpg", 1);//旋转后

    if (!src.data||!src2.data)
    {
        cout << " --(!) Error reading images " << endl;
    }

    //1--初始化SIFT检测算子  
    int minHessian = 40;
    SiftFeatureDetector detector(minHessian);

    //2--使用SIFT算子检测特征点  
    vector<KeyPoint> kp1,kp2;
    detector.detect(src, kp1);
    detector.detect(src2, kp2);

    //--绘制特征点  
    Mat keypointImg, keypointImg2;
    drawKeypoints(src, kp1, keypointImg, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("SIFT kp1", keypointImg);
    cout << "keypoint1 number: " << kp1.size() << endl;

    drawKeypoints(src, kp2, keypointImg2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("SIFT kp2", keypointImg2);
    cout << "keypoint2 number: " << kp2.size() << endl;

    //3--特征向量提取
    SiftDescriptorExtractor extractor;
    Mat descriptor1, descriptor2;
    extractor.compute(src, kp1, descriptor1);
    extractor.compute(src2, kp2, descriptor2);
    //imshow("desc", descriptor1);
    //cout << endl << descriptor1 << endl;

    //4--特征匹配
    BruteForceMatcher<L2<float>> matcher;
    vector<DMatch> matches;
    Mat img_matches;

    matcher.match(descriptor1, descriptor2, matches);
    //--绘制匹配  
    drawMatches(src, kp1, src2, kp2, matches, img_matches);
    imshow("matches", img_matches);

    waitKey(0);
    return 0;
}
// #include<stdio.h>
// #include<iostream>
// #include "opencv2/core/core.hpp"
// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
// using namespace std;
// using namespace cv;

// int main()
// {
//     Mat image = imread("gonglu.jpg");
//     namedWindow("11");
//     imshow("11",image);
    
//     Mat out;
//     GaussianBlur(image,out,Size(3,3),0,0);
//     imshow("gauss_image",out);
//     waitKey(0);

// }