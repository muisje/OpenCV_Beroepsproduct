#include "include/language.h"
#include "include/coloured_shape_finder.h"
#include "include/drawer.h"
#include "include/printer.h"
#include "include/batch_parser.h"
#include "include/specification.h"
#include <opencv2/opencv.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <atomic>
#include <thread>
#include <chrono>
#include <list>
using namespace cv;
using namespace std::literals::chrono_literals;

#define COORDINATE_DEVIATION 80

Language language = Language::DUTCH;
SpecificationMode specMode = SpecificationMode::BATCH;
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
    if (!cap.open(0))
    {
        Printer::print("ERROR: camera not connected!");
        Printer::print("INFO: press enter key to exit.");
        exitProgram.store(true);
    }

    const short maxFrames = 3;

    std::list<std::vector<cv::Vec3f>> resultsCircles;
    std::list<std::vector<DetailedShape>> resultShapes;


    while (exitProgram.load() == false)
    {
        Mat image;
        cap >> image;
        if (image.empty())
            break; // end of video stream

        Specification specCopy = spec.load();
        std::clock_t startTime = std::clock();
        if (specCopy.shape == Shape::CIRCLE)
        {
            resultsCircles.push_back(ColouredShapeFinder::findCircles(image, specCopy.colour));
            if (resultsCircles.size() > maxFrames)
            {
                resultsCircles.pop_front();
                std::vector<cv::Vec3f> resultCircleAvg;

                for (auto & resultCircles : resultsCircles)
                {
                    for (auto & circle : resultCircles)
                    {
                        if (resultCircleAvg.size() == 0)
                        {
                            resultCircleAvg.push_back(circle);   
                        }
                        else
                        {
                            for (auto & item : resultCircleAvg)
                            {
                                if (
                                    item[0] > (circle[0] - COORDINATE_DEVIATION) && item[0] < (circle[0] + COORDINATE_DEVIATION)
                                    &&
                                    item[1] > (circle[1] - COORDINATE_DEVIATION) && item[1] < (circle[1] + COORDINATE_DEVIATION)
                                )
                                {
                                    item[0] = boost::lexical_cast<float>( (item[0] + circle[0]) / 2.0 );
                                    item[1] = boost::lexical_cast<float>( (item[1] + circle[1]) / 2.0 );
                                    item[2] = boost::lexical_cast<float>( (item[2] + circle[2]) / 2.0 );
                                }
                                else
                                {
                                    resultCircleAvg.push_back(circle);
                                }
                            }
                        }
                    }
                }
                std::clock_t endTime = std::clock();
                Drawer::draw(image, resultCircleAvg, specCopy, endTime - startTime);
            }
        }
        else
        {
            resultShapes.push_back(ColouredShapeFinder::find(image, specCopy));
            if (resultShapes.size() > maxFrames)
            {
                resultShapes.pop_front();
                std::vector<DetailedShape> resultShapeAvg;

                for (auto & resultShapes : resultShapes)
                {
                    for (auto & shape : resultShapes)
                    {
                        if (resultShapeAvg.size() == 0)
                        {
                            resultShapeAvg.push_back(shape);   
                        }
                        else
                        {
                            for (auto & item : resultShapeAvg)
                            {
                                if (
                                    item.middlepoint.x > (shape.middlepoint.x - COORDINATE_DEVIATION) && item.middlepoint.x < (shape.middlepoint.x + COORDINATE_DEVIATION)
                                    &&
                                    item.middlepoint.y > (shape.middlepoint.y - COORDINATE_DEVIATION) && item.middlepoint.y < (shape.middlepoint.y + COORDINATE_DEVIATION)
                                )
                                {
                                    try
                                    {
                                        item.middlepoint.y = boost::lexical_cast<int>( (item.middlepoint.y + shape.middlepoint.y) / 2.0);
                                        item.middlepoint.x = boost::lexical_cast<int>( (item.middlepoint.x + shape.middlepoint.x) / 2.0);
                                        }
                                    catch(const std::exception& e)
                                    {
                                        item.middlepoint.y = int( (item.middlepoint.y + shape.middlepoint.y) / 2.0);
                                        item.middlepoint.x = int( (item.middlepoint.x + shape.middlepoint.x) / 2.0);
                                        // std::cerr << e.what() << '\n';
                                    }
                                    item.surface = (item.surface + shape.surface) / 2.0;
                                    

                                }
                                else
                                {
                                    resultShapeAvg.push_back(shape);
                                }
                            }
                        }
                    }
                }
                std::clock_t endTime = std::clock();
                Drawer::draw(image, resultShapeAvg, specCopy, endTime - startTime);
            }
        }


        namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
        imshow("Display Image", image);
        waitKey(30);

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
        initSpec.colour = Colour::YELLOW;
        initSpec.shape = Shape::CIRCLE;
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