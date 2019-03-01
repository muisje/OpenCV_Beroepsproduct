
#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/specification.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sstream>
#include <iterator>
#include <atomic>
#include <thread>
#include <ctime>
using namespace cv;

bool interactive = true;
bool live = true;
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
    while (exitProgram.load() == false)
    {
        Mat image;
        cap >> image;
        if (image.empty())
            break; // end of video stream

        specCopy = spec.load();
        if (specCopy.shape == Shape::CIRCLE)
        {
            std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
            Drawer::draw(image, circles, specCopy);
        }
        else
        {
            std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
            Drawer::draw(image, shapes, specCopy);
        }
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
    while (exitProgram.load() == false)
    {
        Mat image = orginal.clone();
        specCopy = spec.load();
        if (specCopy.shape == Shape::CIRCLE)
        {
            std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
            Drawer::draw(image, circles, specCopy);
        }
        else
        {
            std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
            Drawer::draw(image, shapes, specCopy);
        }
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
    if (!interactive)
    {
        Specification staticSpec;
        staticSpec.colour = Colour::BLUE;
        staticSpec.shape = Shape::RECTANGLE;
        spec.store(staticSpec);
    }
    else
    {
        Specification unkownSpec;
        unkownSpec.colour = Colour::UNKNOWN_COLOUR;
        unkownSpec.shape = Shape::UNKNOWN_SHAPE;
        spec.store(unkownSpec);
    }

    std::thread stream(detectAndDraw, live);

    while (!exitProgram.load() && interactive)
    {
        std::cout << "Enter: [shape][whitespace][colour]" << std::endl;
        std::string input;

        std::getline(std::cin, input);
        if (input == "exit")
        {
            exitProgram.store(true);
        }
        std::istringstream iss(input);
        std::string shape;
        std::string colour;
        std::vector<std::string> pieces;

        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(), back_inserter(pieces));
        if (pieces.size() >= 2)
        {
            Specification tempSpec;
            tempSpec = parseSpecification(pieces[0], pieces[1]);
            spec.store(tempSpec);
            if (tempSpec.colour == UNKNOWN_COLOUR || tempSpec.shape == UNKNOWN_SHAPE)
            {
                std::cout << "Unknown colour or shape!" << std::endl;
            }
        }
        else
        {
            std::cout << "Unknown colour or shape!" << std::endl;
        }
    }

    stream.join();
    return 0;
}