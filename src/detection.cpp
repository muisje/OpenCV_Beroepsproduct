#include "../include/detection.h"
#include "../include/coloured_shape_finder.h"
#include "../include/drawer.h"
#include "../include/detection.h"
#include "../include/printer.h"
#include <opencv2/opencv.hpp>
#include <boost/lexical_cast.hpp>
#include <list>

void Detection::detectAndDrawOnce(cv::Mat image, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, Language language)
{
    Specification specCopy = spec->load();
    if (specCopy.shape == Shape::CIRCLE)
    {
        std::clock_t startTime = std::clock();
        std::vector<cv::Vec3f> circles = ColouredShapeFinder::findCircles(image, specCopy.colour);
        std::clock_t endTime = std::clock();
        if (needToPrint->load())
        {
            Printer::print(specificationToString(specCopy, language));
            if (circles.size() == 0)
            {
                Printer::printNotFound(endTime - startTime);
            }
            Printer::print(circles, endTime - startTime);
            needToPrint->store(false);
        }
        Drawer::draw(image, circles, specCopy, endTime - startTime);
    }
    else
    {
        std::clock_t startTime = std::clock();

        std::vector<DetailedShape> shapes = ColouredShapeFinder::find(image, specCopy);
        std::clock_t endTime = std::clock();

        if (needToPrint->load())
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
            needToPrint->store(false);
        }
        Drawer::draw(image, shapes, specCopy, endTime - startTime);
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE); // Create Window
    imshow("Display Image", image);
    waitKey(30);
}

void Detection::detectAndDrawLive(std::atomic<bool>* exitProgram,std::atomic<Specification>* spec, short camera)
{
    //TODO take avg of multiple frames
    VideoCapture cap;
    if (!cap.open(camera))
    {
        Printer::print("ERROR: camera not connected!");
        Printer::print("INFO: press enter key to exit.");
        exitProgram->store(true);
    }

    const short maxFrames = 3;

    std::list<std::vector<cv::Vec3f>> resultsCircles;
    std::list<std::vector<DetailedShape>> resultShapes;


    while (exitProgram->load() == false)
    {
        Mat image;
        cap >> image;
        if (image.empty())
            break; // end of video stream

        Specification specCopy = spec->load();
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

void Detection::detectAndDrawStatic(std::atomic<bool>* exitProgram, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, const std::string & imageFileName, Language language)
{
    Mat orginal = imread(imageFileName, IMREAD_COLOR);
    while (exitProgram->load() == false)
    {
        detectAndDrawOnce(orginal.clone(),spec,needToPrint,language);
    }
}
