#include "../include/coloured_shape_finder.h"
#include "../include/shape_filter.h"
#include "../include/colour_filter.h"
#include "../include/printer.h"
#include <opencv2/opencv.hpp>

ColouredShapeFinder::ColouredShapeFinder()
{
}

ColouredShapeFinder::~ColouredShapeFinder()
{
}

std::vector<DetailedShape> ColouredShapeFinder::find(cv::Mat image, Specification specification)
{
    std::vector<DetailedShape> detailedShapes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::Mat hsvImage;
    cvtColor(image, hsvImage, CV_BGR2HSV);
    hsvImage = ColourFilter::preserveColour(hsvImage, specification.colour);

    hsvImage = ShapeFilter::removeSmallContours(hsvImage);
    cv::findContours(hsvImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    for (size_t i = 0; i < contours.size(); ++i)
    {
        std::vector<cv::Point> approx;
        approxPolyDP(contours[i], approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.03, true);
        switch (specification.shape)
        {
        case RECTANGLE:
        case SQUARE:
        case QUADRANGLE:
            if (approx.size() == 4)
            {
                if (ShapeFilter::isShape(approx, specification.shape))
                {
                    DetailedShape shape = DetailedShape(contours[i], specification);
                    if (shape.surface > MINIMUM_SURFACE)
                    {
                        detailedShapes.push_back(shape);
                    }
                }
            }
            break;
        case CIRCLE:
            if (ShapeFilter::isCircle(contours[i]))
            {
                DetailedShape shape = DetailedShape(contours[i], specification);
                if (shape.surface > MINIMUM_SURFACE)
                {
                    detailedShapes.push_back(shape);
                }
            }
            break;
        case TRIANGLE:
            if (approx.size() == 3 && !ShapeFilter::isHalfCircle(contours[i])) // When an halfCircle is to small approxPolyDP in rare occasions only recognizes 3 "corners"
            {
                DetailedShape shape = DetailedShape(contours[i], specification);
                if (shape.surface > MINIMUM_SURFACE)
                {
                    detailedShapes.push_back(shape);
                }
            }
            break;
        case HALF_CIRCLE:
            if (ShapeFilter::isHalfCircle(contours[i]))
            {
                DetailedShape shape = DetailedShape(contours[i], specification);
                if (shape.surface > MINIMUM_SURFACE)
                {
                    detailedShapes.push_back(shape);
                }
            }
            break;
        case UNKNOWN_SHAPE:
        case NO_SHAPE:
            return detailedShapes;
            break;
        }
    }
    return detailedShapes;
}

std::vector<cv::Vec3f> ColouredShapeFinder::findCircles(cv::Mat image, enum ::Colour colour)
{
    cv::Mat dst_x = image.clone();
    cv::Mat dst_y = image.clone();
    cv::Mat dst_combined = image.clone();

    cv::Scharr(image, dst_x, -1, 1, 0, 1.0, 300);
    cv::Scharr(image, dst_y, -1, 0, 1, 1.0, 300);

    cv::addWeighted(dst_x, 0.5, dst_y, 0.5, 0, dst_combined);

    cv::Mat hsv;
    cvtColor(image, hsv, CV_BGR2HSV);
    cv::Mat foundCircles = ColourFilter::preserveColour(hsv, colour);
    cvtColor(dst_combined, dst_combined, cv::COLOR_BGR2GRAY);
    subtract(foundCircles, dst_combined, foundCircles);

    cv::GaussianBlur(foundCircles, foundCircles, cv::Size(5, 5), 3, 3); // perfect 

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(foundCircles, circles, CV_HOUGH_GRADIENT, 1, foundCircles.rows / 8, 100, 30, 15, 100);
    return circles;
}