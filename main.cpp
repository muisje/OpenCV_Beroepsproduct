#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "include/colour_filter.h"
#include "include/shape_filter.h"
#include "include/shape.h"
#include "include/specification.h"
using namespace cv;

bool interactive = false;

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
    cvtColor(image, hsv, CV_BGR2HSV); 
    Mat test1;
    Mat test2;
    ColourFilter cf = ColourFilter();
    ShapeFilter sf = ShapeFilter();

    if (!interactive)
    {
        enum::Shape shape = Shape::CIRCLE;
        enum::Colour colour = Colour::YELLOW;

        Specification spec;
        spec.shape = shape;
        spec.colour = colour;


        if (shape == Shape::CIRCLE)
        {
            Mat dst_x = image.clone();
            Mat dst_y = image.clone();
            Mat dst_combined = image.clone();

            Scharr(image, dst_x, -1, 1, 0, 1.0, 300);
            Scharr(image, dst_y, -1, 0, 1, 1.0, 300);
                
            addWeighted(dst_x, 0.5, dst_y, 0.5, 0, dst_combined);

            Mat foundCircles = cf.preserveColour(hsv, Colour::YELLOW);
            cvtColor(dst_combined, dst_combined, COLOR_BGR2GRAY);
            subtract(foundCircles, dst_combined, foundCircles);

            cv::GaussianBlur(foundCircles, foundCircles, cv::Size(3, 3), 3, 3); // perfect for wood 
            //TODO find blur for surface of blocks (so its flat, smooth and solid)
            // cv::GaussianBlur(foundCircles, foundCircles, cv::Size(5, 5), 3, 3); // perfect for yellow

            std::vector<cv::Vec3f> circles;
            cv::HoughCircles(foundCircles, circles, CV_HOUGH_GRADIENT, 1, foundCircles.rows / 8, 100, 30, 15, 100);


            // Loop over all detected circles and outline them on the origi`nal image
            if (circles.size() != 0)
            {
                for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
                {
                    cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
                    int radius = std::round(circles[current_circle][2]);


                    double area = M_PI * pow(radius, 2);

                    std::string textCenter = "(" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
                    std::string textArea = std::to_string(int(round(area))) + " px^2"; 
                    std::string textTicks = "000 ms";
                    std::string text = textCenter + " " + textArea + " " + textTicks;


                    cv::circle(image, center, 1, cv::Scalar(0, 0, 0), 3); // center
                    cv::circle(image, center, radius, cv::Scalar(0, 0, 0), 3); // contour

                    Size textSize = getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                                1, 1, 0);
                    putText(image, text, cv::Point(center.x  - (textSize.width/2), center.y - radius - 6), CV_FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
                    std::cout << text << std::endl;
                }
            } 
            else
            {
                std::string textNotFound = "Not Found";
                std::string textTicks = "000 ms";
                std::string text = textNotFound + " " + textTicks;

                Size textSize = getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                                1, 1, 0);
                putText(image, text, cv::Point((image.cols/2)  - (textSize.width/2), (image.rows/2) - (textSize.height/2)), CV_FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
                std::cout << text << std::endl;
            }
            
        }
        else
        {
            image = sf.preserveShape(cf.preserveColour(image, colour), spec);
        }
        


        namedWindow("Display Image", WINDOW_AUTOSIZE);
        cv::resize(image, image, cv::Size(0, 0), 1, 1);

        imshow("Display Image", image);
        waitKey(0);
    }
    else
    {
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
    }
    
    return 0;
}