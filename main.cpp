#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/specification.h"
#include <atomic>
#include <thread>
#include <ctime>
using namespace cv;

bool interactive = true;
std::atomic<bool> programActive;
Specification specification{UNKNOWN_SHAPE, UNKNOWN_COLOUR};

void readSpecification(/*Specification specification, std::atomic<bool> programActive*/)
{
    while (programActive)
    {
        std::cout << "Enter: [colour][whitespace][shape]" << std::endl;
        std::string input;

        std::getline(std::cin, input);
        if (input == "exit")
        {
            programActive = false;
        }

        specification = parseSpecification(input[0], input[2]);
        if (specification.colour == UNKNOWN_COLOUR || specification.shape == UNKNOWN_SHAPE)
        {
            std::cout << "Unknown colour or shape!" << std::endl;
        }
    }
}

int main(/*int argc, char **argv*/) // Warning unused parameter
{
    programActive = true;
    Specification previousSpecification = specification;
    Mat image = imread("../testImages/testImage8.jpg", IMREAD_COLOR);
    Mat image1;
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    if (!interactive)
    {
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
    }
    else
    {
        std::thread t1(readSpecification);
        t1.detach();
        while (programActive)
        {

            //enter for example the following
            //"y h"
            // this will show you all yellow half circles
            //"b r" will show you all blue rectangles etc etc.
            if (previousSpecification != specification)
            {
                std::clock_t start;
                double duration;

                start = std::clock();
                previousSpecification = specification;
                image1 = image.clone();

                if (specification.shape == Shape::CIRCLE)
                {
                    std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specification.colour);
                    Drawer::draw(image1, circles);
                }
                else
                {
                    std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specification);
                    Drawer::draw(image1, shapes);
                }
                imshow("Display Image", image1);
                waitKey(150);

                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

                std::cout << "printf: " << duration << '\n';
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    std::cout << "Shutting down" << std::endl;
    return 0;
}