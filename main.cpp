#include <thread>
#include <atomic>

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/specification.h"

using namespace cv;

bool interactive = false;
bool live = false;
std::atomic<bool> exitProgram(false);
std::atomic<Specification> spec;


void detectAndDrawLive()
{
    //TODO take avg of multiple frames
    VideoCapture cap;
    if (!cap.open(0))
    {
        // error?
    }
    Specification specCopy;
    while(exitProgram.load() == false)
    {
        Mat image;
        cap >> image;
        if (image.empty())
            break; // end of video stream

        specCopy = spec.load();
        if (specCopy.shape == Shape::CIRCLE)
        {
            std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
            Drawer::draw(image, circles);
        }
        else
        {
            std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
            Drawer::draw(image, shapes);
        }
        namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
        imshow("Display Image", image);
        waitKey(1);
    }
    cap.release();
    cv::destroyWindow("Display Image");
}

void detectAndDrawStatic()
{
    Mat orginal = imread("../testImages/testImage8.jpg", IMREAD_COLOR);
    Specification specCopy;
    while(exitProgram.load() == false)
    {
        Mat image = orginal.clone();
        specCopy = spec.load();
        if (specCopy.shape == Shape::CIRCLE)
        {
            std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
            Drawer::draw(image, circles);
        }
        else
        {
            std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
            Drawer::draw(image, shapes);
        }
        namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
        imshow("Display Image", image);
        waitKey(150);
    }
}


void detectAndDraw(bool live)
{
    if (live)
    {
        detectAndDrawLive();
    }
    else
    {
        detectAndDrawStatic();
    }
}

int main(/*int argc, char **argv*/) // Warning unused parameter
{
    if(!interactive)
    {
        Specification staticSpec;
        staticSpec.colour = Colour::BLUE;
        staticSpec.shape = Shape::RECTANGLE;
        spec.store(staticSpec);
    }


    std::thread stream(detectAndDraw, live);

    while(!exitProgram.load())
    {   
        std::cout << "Enter: [colour][whitespace][shape]" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        if (input == "exit")
        {
            exitProgram.store(true);
        }
        spec.store(parseSpecification(input[0], input[2]));
    }
    stream.join();

    return 0;
}