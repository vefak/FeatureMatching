#include "filter.h"

int main( )
{

    
    bool showImages = false;
    bool saveImages = true;
    Mat img_object_rotated = imread("./img/Small_area_rotated.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_object_normal = imread("./img/Small_area.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat image = imread( "./img/StarMap.png" , CV_LOAD_IMAGE_GRAYSCALE );
    
    vector<Point2f> corners_n, corners_r;

    corners_n = findingPlanar(image,  img_object_normal,  showImages, saveImages, 25, 0.80f);
    corners_r = findingPlanar(image,  img_object_rotated,  showImages, saveImages, 10, 0.79f);

    displayCorners("Normal", corners_n);
    displayCorners( "Rotated", corners_r);

    return 0;
}


