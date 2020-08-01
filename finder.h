#ifndef finder_H
#define finder_H
 
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class Finder
{
    

public:
    int hessian;
    float lowe_ratio;     
    explicit Finder(int x, float y);
    void showImages(Mat img);
    Mat homography_finder(Mat img1, Mat img2);
    void printtt() const;

};
 #endif
