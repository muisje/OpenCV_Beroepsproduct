#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "include/colour_filter.h"
#include "include/shape_filter.h"
#include "include/shape.h"
using namespace cv;

int main(int argc, char **argv)
{
    Mat image= imread("../testImages/blokjes2.jpg", IMREAD_COLOR );
    cv::resize(image,image, cv::Size(0,0),0.8,0.8);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
	Mat hsv;
    cvtColor(image,hsv, CV_BGR2HSV);
	ColourFilter cf = ColourFilter();
    ShapeFilter sf = ShapeFilter();
    Mat finalImage = cf.preserveColour(hsv,RED);
    Mat finalImage2 = sf.preserveShape(finalImage,TRIANGLE);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", finalImage2);

    waitKey(0);

    return 0;
}