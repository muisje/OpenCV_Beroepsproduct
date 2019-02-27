#include <thread>
#include <atomic>

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/specification.h"

using namespace cv;

bool interactive = true;
bool live = true;
std::atomic<bool> exitProgram(false);
// std::atomic_bool exit;
std::atomic<Specification> spec;


void detectAndDraw()
{
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
}


int main(/*int argc, char **argv*/) // Warning unused parameter
{
    // take avg of three frames
    if (live)
    {

        std::thread stream(detectAndDraw);
        // VideoCapture cap;
        // if (!cap.open(0))
        //     return 1;


        // if (!interactive)
        // {
        //     enum ::Shape shape = Shape::RECTANGLE;
        //     enum ::Colour colour = Colour::BLUE;
        //     spec.shape = shape;
        //     spec.colour = colour;
        // }

        while(true)
        {    
            // Mat image;
            // cap >> image;
            // if (image.empty())
            //     break; // end of video stream

            if (interactive)
            {
                std::string input;
                std::cout << "Enter: [colour][whitespace][shape]" << std::endl;
                std::getline(std::cin, input);
                if (input == "exit")
                {
                    exitProgram.store(true);
                    // return 0;
                }
                // Mat image1 = image.clone();

                spec.store(parseSpecification(input[0], input[2]));

            }

            // if (spec.shape == Shape::CIRCLE)
            // {
            //     std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, spec.colour);
            //     Drawer::draw(image, circles);
            // }
            // else
            // {
            //     std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, spec);
            //     Drawer::draw(image, shapes);
            // }
            // namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
            // imshow("Display Image", image);
            // waitKey(30);
        }

        stream.join();
        // cv::releaseCapture(cap);
        // cvDestroyWindow("Display Image");
    }
    else
    {
        Mat image = imread("../testImages/webcam2.jpg", IMREAD_COLOR);
        std::string input;
        if (!image.data)
        {
            printf("No image data \n");
            return -1;
        }
    }

    // if (!interactive)
    // {

    //     enum ::Shape shape = Shape::CIRCLE;
    //     enum ::Colour colour = Colour::BLUE;

    //     Specification spec;
    //     spec.shape = shape;
    //     spec.colour = colour;

    //     if (shape == Shape::CIRCLE)
    //     {
    //         std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, spec.colour);
    //         Drawer::draw(image, circles);
    //     }
    //     else
    //     {
    //         std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, spec);
    //         Drawer::draw(image, shapes);
    //     }

    //     // cv::resize(image, image, cv::Size(0, 0), 1, 1);
    //     imshow("Display Image", image);
    //     waitKey(0);
    // }
    // else
    // {
    //     while (true)
    //     {
    //         //enter for example the following
    //         //"y h"
    //         // this will show you all yellow half circles
    //         //"b r" will show you all blue rectangles etc etc.
    //         std::cout << "Enter: [colour][whitespace][shape]" << std::endl;
    //         std::getline(std::cin, input);
    //         if (input == "exit")
    //         {
    //             return 0;
    //         }
    //         Mat image1 = image.clone();

    //         Specification specification = parseSpecification(input[0], input[2]);

    //         if (specification.shape == Shape::CIRCLE)
    //         {
    //             std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specification.colour);
    //             Drawer::draw(image1, circles);
    //         }
    //         else
    //         {
    //             std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specification);
    //             Drawer::draw(image1, shapes);
    //         }

    //         imshow("Display Image", image1);
    //         waitKey(150);
    //     }
    // }

    return 0;
}