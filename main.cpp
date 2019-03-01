
#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/printer.h"
#include "include/parser.h"
#include "include/specification.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sstream>
#include <iterator>
#include <atomic>
#include <thread>
#include <ctime>
#include <chrono>
using namespace cv;
using namespace std::literals::chrono_literals;

enum SpecificationMode {INTERACTIVE, BATCH, PRE_DEFINED};

SpecificationMode specMode = SpecificationMode::BATCH;
bool live = false;
std::atomic<bool> exitProgram(false);
std::atomic<bool> needToPrint(false);
std::atomic<Specification> spec;


void detectAndDrawOnce(cv::Mat image, uint wait = 1)
{
    Specification specCopy = spec.load();
    if (specCopy.shape == Shape::CIRCLE)
    {
        std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
        
        if (needToPrint.load())
        {
            if (circles.size() == 0)
            {
                Printer::printNotFound();
            }
            Printer::print(circles);
            needToPrint.store(false);
        }
        Drawer::draw(image, circles, specCopy);
    }
    else
    {
        std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);

        if (needToPrint.load())
        {
            if (shapes.size() == 0)
            {
                Printer::printNotFound();
            }
            else
            {
                Printer::print(shapes);
            }
            std::cout << std::endl;
            needToPrint.store(false);
        }
        Drawer::draw(image, shapes, specCopy);
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
    imshow("Display Image", image);
    waitKey(wait);
}

void detectAndDrawLive()
{
    //TODO take avg of multiple frames
    VideoCapture cap;
    if (!cap.open(0))
    {
        std::cout << "ERROR: camera not connected!" << std::endl;
        std::cout << "INFO: press enter key to exit." << std::endl;
        exitProgram.store(true);
    }
    while (exitProgram.load() == false)
    {
        Mat image;
        cap >> image;
        if (image.empty())
            break; // end of video stream

        detectAndDrawOnce(image);
    }
    cap.release();
    cv::destroyWindow("Display Image");
}

void detectAndDrawStatic()
{
    Mat orginal = imread("../testImages/testImage8.jpg", IMREAD_COLOR);
    uint wait = 0;
    if (specMode == SpecificationMode::BATCH)
    {
        wait = 30;
    }
    while (exitProgram.load() == false)
    {
        detectAndDrawOnce(orginal.clone(), wait);
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
    Specification initSpec;
    switch (specMode)
    {
        case SpecificationMode::PRE_DEFINED:
            initSpec.colour = Colour::BLUE;
            initSpec.shape = Shape::RECTANGLE;
            break;
    
        default:
            initSpec.colour = Colour::UNKNOWN_COLOUR;
            initSpec.shape = Shape::UNKNOWN_SHAPE;
            break;
    }
    spec.store(initSpec);

    std::thread stream(detectAndDraw, live);
    
    if (specMode == SpecificationMode::INTERACTIVE)
    {
        while (!exitProgram.load())
        {
            std::cout << "Enter: [colour][whitespace][shape]" << std::endl;
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
    }
    else if (specMode == SpecificationMode::BATCH) {
        if (live)
        {
            std::this_thread::sleep_for(2s); // Wait for camara to turn on
        }
        Parser batch("../batch_english.txt");
        while (!exitProgram.load())
        {
            Specification currentSpec = batch.nextSpecification();
            if (currentSpec.shape == Shape::NO_SHAPE || currentSpec.colour == Colour::NO_COLOUR)
            {
                exitProgram.store(true);
            }
            else
            {
                spec.store(currentSpec);
                needToPrint.store(true);
            }
            std::this_thread::sleep_for(1000ms);
        }
    }
    stream.join();
    return 0;
}