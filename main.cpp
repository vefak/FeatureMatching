#include "finder.h"
#include <iostream>

using namespace std;


bool showImages = false;



int main( )
{
    Mat img1 = imread("./img/Small_area.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img2 = imread( "./img/StarMap.png" , CV_LOAD_IMAGE_GRAYSCALE );
    Mat img3 = imread( "./img/Small_area_rotated.png" , CV_LOAD_IMAGE_GRAYSCALE );

    Finder test1(20, 0.90f);
    Finder test2(10, 0.90f);
    Mat result1, result2;
}

