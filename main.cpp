#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "include/colour_filter.h"
#include "include/shape_filter.h"
#include "include/shape.h"
#include "include/specification.h"
using namespace cv;

int een = 5;
int twee = 85;
int drie = 85;
int main(/*int argc, char **argv*/) // Warning unused parameter
{
    Mat image = imread("../testImages/testImage3.jpg", IMREAD_COLOR);
    Mat hsv;
    std::string input;
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    while (true)
    {
        //enter for example the following
        //"y h"
        // this will show you all yellow half circles
        //"b r" will show you all blue rectangles etc etc.
        std::getline(std::cin, input);
        Specification specification = parseSpecification(input[0], input[2]);
        cvtColor(image, hsv, CV_BGR2HSV);
        Mat test1;
        ColourFilter cf = ColourFilter();
        ShapeFilter sf = ShapeFilter();
        cv::bilateralFilter(hsv, test1, een, twee, drie);
        Mat finalImage = cf.preserveColour(test1, specification.colour);
        // cvtColor(finalImage,finalImage,CV_GRAY2BGR);
        // Mat test;
        // cv::bitwise_and(finalImage, image, test);
        // imshow("test",test);
        // Canny(test,test2,60,60);
        // imshow("test2",test2);
        Mat test2;

        cv::bilateralFilter(finalImage, test2, een, twee, drie);

        Mat finalImage2 = sf.preserveShape(test2, specification);
        namedWindow("Display Image", WINDOW_AUTOSIZE);
        cv::resize(finalImage2, finalImage2, cv::Size(0, 0), 0.8, 0.8);

        imshow("Display Image", finalImage2);
        if(waitKey(30) >= 0){};
    }
    return 0;
}