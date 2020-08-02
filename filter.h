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


vector<Point2f> findingPlanar(Mat img_scene, Mat img_object, bool showImages, bool saveImages,  int hessian, float ratio);
void displayCorners( string namecorner, vector<Point2f> corners);
void savingImage(string nameimage, Mat Image);
