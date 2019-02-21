#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "include/colour_filter.h"
#include "include/shape_filter.h"
#include "include/shape.h"
using namespace cv;

int een = 5;
int twee = 85;
int drie = 85;
int main(int argc, char **argv)
{
    Mat image = imread("../testImages/testImage3.jpg", IMREAD_COLOR);
    // cv::resize(image, image, cv::Size(0, 0), 0.5, 0.5);
    Mat hsv;

    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    cvtColor(image, hsv, CV_BGR2HSV); 
    Mat test1;
    Mat test2;
    ColourFilter cf = ColourFilter();
    ShapeFilter sf = ShapeFilter();
    cv::bilateralFilter(hsv, test1, een, twee, drie);
    Mat finalImage = cf.preserveColour(test1, YELLOW);
    cv::bilateralFilter(finalImage, test2, een, twee, drie);

    Mat finalImage2 = sf.preserveShape(test2, RECTANGLE);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::resize(finalImage2, finalImage2, cv::Size(0, 0), 0.8, 0.8);

    imshow("Display Image", finalImage2);
    waitKey(0);

    return 0;
}