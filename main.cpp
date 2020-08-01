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


vector<Point2f> findingPlanar(Mat img_scene, Mat img_object, bool showImages, int hessian, float ratio);
void displayCorners(string namecorner, vector<Point2f> corners);



int main( )
{

    
    bool showImages = false;
    Mat img_object_rotated = imread("./img/Small_area_rotated.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_object_normal = imread("./img/Small_area.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat image = imread( "./img/StarMap.png" , CV_LOAD_IMAGE_GRAYSCALE );
    
    vector<Point2f> corners_n, corners_r;

    corners_n = findingPlanar(image,  img_object_normal,  showImages, 25, 0.80f);
    corners_r = findingPlanar(image,  img_object_rotated,  showImages, 10, 0.79f);

    displayCorners("Normal", corners_n);
    displayCorners("Rotated", corners_r);
    return 0;
}




vector<Point2f> findingPlanar(Mat img_scene, Mat img_object, bool showImages, int hessian, float ratio) {
    
    GaussianBlur(img_object,img_object,  Size(7,7),0,0);
    GaussianBlur(img_scene,img_scene, Size(7,7),0,0);

    if ( img_object.empty() || img_scene.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
    
    }

    cout << "Size of Image Object: " <<  img_object.size() << endl;
    cout << "Size of Image Scene: " <<  img_scene.size() << endl;


    if(showImages){

    namedWindow( "Object", WINDOW_AUTOSIZE );
    imshow( "Object", img_object );                  
    
    namedWindow( "Main Image", WINDOW_AUTOSIZE );
    imshow( "Main Image", img_scene );   
    }
    

    int minHessian = hessian;
    Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<KeyPoint> keypoints_object, keypoints_scene;
    Mat descriptors_object, descriptors_scene;
    detector->detectAndCompute( img_object, noArray(), keypoints_object, descriptors_object );
    detector->detectAndCompute( img_scene, noArray(), keypoints_scene, descriptors_scene );
    
    
  

    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors_object, descriptors_scene, knn_matches, 2 );
    const float ratio_thresh = ratio;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    cout << good_matches.size() << endl;
   
    Mat img_matches;
    drawMatches( img_object, keypoints_object, img_scene, keypoints_scene, good_matches, img_matches, Scalar::all(-1),
                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );


    std::vector<Point2f> obj;
    std::vector<Point2f> scene;
    for( size_t i = 0; i < good_matches.size(); i++ )
    {
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }
    Mat H = findHomography( obj, scene, RANSAC );
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = Point2f(0, 0);
    obj_corners[1] = Point2f( (float)img_object.cols, 0 );
    obj_corners[2] = Point2f( (float)img_object.cols, (float)img_object.rows );
    obj_corners[3] = Point2f( 0, (float)img_object.rows );
    std::vector<Point2f> scene_corners(4);

    
    perspectiveTransform( obj_corners, scene_corners, H);

    line( img_matches, scene_corners[0] + Point2f((float)img_object.cols, 0),
          scene_corners[1] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4 );
    line( img_matches, scene_corners[1] + Point2f((float)img_object.cols, 0),
          scene_corners[2] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[2] + Point2f((float)img_object.cols, 0),
          scene_corners[3] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[3] + Point2f((float)img_object.cols, 0),
          scene_corners[0] + Point2f((float)img_object.cols, 0), Scalar( 0, 255, 0), 4 );

    imshow("Good Matches & Object detection", img_matches );
    waitKey();

    return obj_corners;

}




void displayCorners(string namecorner, vector<Point2f> corners){
  cout << "--- " << namecorner << " ---"  << endl;

  for(int i=0; i < corners.size(); i++){

    cout << corners.at(i) << ' ';
  }
  cout << "  \n"  << endl;

}
