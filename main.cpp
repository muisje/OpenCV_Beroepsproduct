#include "include/language.h"
#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/printer.h"
#include "include/batch_parser.h"
#include "include/specification.h"
#include <opencv2/opencv.hpp>
#include <iterator>
#include <atomic>
#include <thread>
#include <chrono>
using namespace cv;
using namespace std::literals::chrono_literals;

Language language = Language::DUTCH;
SpecificationMode specMode = SpecificationMode::INTERACTIVE;
bool live = false;
std::atomic<bool> exitProgram(false);
std::atomic<bool> needToPrint(false);
std::atomic<Specification> spec;

void detectAndDrawOnce(cv::Mat image)
{
    Specification specCopy = spec.load();
    if (specCopy.shape == Shape::CIRCLE)
    {
        std::clock_t startTime = std::clock();
        std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
        std::clock_t endTime = std::clock();
        if (needToPrint.load())
        {
            Printer::print(specificationToString(specCopy, language));
            if (circles.size() == 0)
            {
                Printer::printNotFound(endTime - startTime);
            }
            Printer::print(circles, endTime - startTime);
            needToPrint.store(false);
        }
        Drawer::draw(image, circles, specCopy, endTime - startTime);
    }
    else
    {
        std::clock_t startTime = std::clock();

        std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
        std::clock_t endTime = std::clock();

        if (needToPrint.load())
        {
            Printer::print(specificationToString(specCopy, language));
            if (shapes.size() == 0)
            {
                Printer::printNotFound(endTime - startTime);
            }
            else
            {
                Printer::print(shapes, endTime - startTime);
            }
            needToPrint.store(false);
        }
        Drawer::draw(image, shapes, specCopy, endTime - startTime);
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
    imshow("Display Image", image);
    waitKey(30);
}

void detectAndDrawLive()
{
    //TODO take avg of multiple frames
    VideoCapture cap;
    if (!cap.open(1))
    {
        Printer::print("ERROR: camera not connected!");
        Printer::print("INFO: press enter key to exit.");
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
    Mat orginal = imread("../testImages/testImage3.jpg", IMREAD_COLOR);
    while (exitProgram.load() == false)
    {
        detectAndDrawOnce(orginal.clone());
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
        switch (language)
        {
        case Language::ENGLISH:
            Printer::print("Enter: [shape][whitespace][colour]");
            break;

        case Language::DUTCH:
            Printer::print("Voer in: [vorm][whitespace][kleur]");
            break;

        default:
            Printer::print("Warning: unsupported language");
            break;
        }
        while (!exitProgram.load())
        {
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

                std::string colour = toEnglish(toUpper(pieces[0]), language);
                std::string shape = toEnglish(toUpper(pieces[1]), language);
                tempSpec = parseSpecification(colour, shape);
                spec.store(tempSpec);
                if (tempSpec.colour == UNKNOWN_COLOUR || tempSpec.shape == UNKNOWN_SHAPE)
                {
                    Printer::print("Unknown colour or shape!");
                }
            }
            else
            {
                Printer::print("Unknown colour or shape!");
            }
        }
    }
    else if (specMode == SpecificationMode::BATCH)
    {
        if (live)
        {
            std::this_thread::sleep_for(2s); // Wait for camara to turn on
        }
        std::string batchFile;
        if (language == Language::DUTCH)
        {
            batchFile = "../batch.txt";
        }
        else
        {
            batchFile = "../batch_english.txt";
        }

        BatchParser batch(batchFile, language);
        int batchNumber = 0;
        while (!exitProgram.load())
        {
            Specification currentSpec = batch.nextSpecification();
            ++batchNumber;

            if (currentSpec.shape == Shape::NO_SHAPE || currentSpec.colour == Colour::NO_COLOUR)
            {
                exitProgram.store(true);
            }
            else if (
                currentSpec.shape == Shape::UNKNOWN_SHAPE || currentSpec.colour == Colour::UNKNOWN_COLOUR)
            {
                Printer::printUnknown(batchNumber);
            }
            else
            {
                spec.store(currentSpec);
                needToPrint.store(true);
                std::this_thread::sleep_for(1000ms);
            }
        }
    }
    stream.join();
    return 0;
}