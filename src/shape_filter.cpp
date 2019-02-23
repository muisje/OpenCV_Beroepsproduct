#include "../include/shape_filter.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

ShapeFilter::ShapeFilter()
{
}

ShapeFilter::~ShapeFilter()
{
}

cv::Mat ShapeFilter::preserveShape(cv::Mat inputMat, Specification specification)
{
       
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(inputMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    inputMat = removeSmallContours(inputMat, contours);
    for (size_t i = 0; i < contours.size(); ++i)
    {
        std::vector<cv::Point> approx;
        approxPolyDP(contours[i], approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.05, true);
        switch (specification.shape)
        {
        case RECTANGLE:
        case SQUARE:
        case QUADRANGLE:
            if (approx.size() == 4)
            {
                if (isShape(approx, specification.shape))
                {
                    foundContours.push_back(contours[i]);
                    foundShape.push_back(DetailedShape(contours[i], specification));
                }
            }
            break;
        case CIRCLE:
            std::cout << "Not implemented" << std::endl;
            break;
        case TRIANGLE:
            if (approx.size() == 3 && !isHalfCircle(contours[i])) // When an halfCircle is to small approxPolyDP in rare occasions only recognizes 3 "corners"
            {
                foundContours.push_back(contours[i]);
                foundShape.push_back(DetailedShape(contours[i], specification));
            }
            break;
        case HALF_CIRCLE:
            if (isHalfCircle(contours[i]))
            {
                foundContours.push_back(contours[i]);
                foundShape.push_back(DetailedShape(contours[i], specification));
            }
            break;
        }
    }
    cv::cvtColor(inputMat, inputMat, cv::COLOR_GRAY2BGR);
    cv::drawContours(inputMat, foundContours, -1, cv::Scalar(255, 0, 0), 6, 6);
    return inputMat;
}

bool ShapeFilter::isShape(std::vector<cv::Point> approx, Shape preservedShape)
{
    float length1, length2, length3, length4;
    bool allAnglesAreStraight;
    for (int i = 0; i < 4; ++i)
    {
        double angle = calculateAngle(approx[(0 + i) % 4], approx[(1 + i) % 4], approx[(2 + i) % 4]);

        if (angle > RIGHT_ANGLE + ANGLE_DEVIATION || angle < RIGHT_ANGLE - ANGLE_DEVIATION)
        {
            allAnglesAreStraight = false;
            i = 5;
        }
    }
    length1 = (float)calculateDistance(approx[0], approx[1]);
    length2 = (float)calculateDistance(approx[1], approx[2]);
    length3 = (float)calculateDistance(approx[2], approx[3]);
    length4 = (float)calculateDistance(approx[3], approx[0]);
    if (length1 > MINIMUM_LENGTH && length2 > MINIMUM_LENGTH && length3 > MINIMUM_LENGTH && length4 > MINIMUM_LENGTH)
    {
        if (allAnglesAreStraight && preservedShape == SQUARE)
        {
            if (abs(length1 - length2) < LENGTH_DEVIATION || abs(length3 - length4) < LENGTH_DEVIATION)
            {
                return true;
            }
        }
        else if (allAnglesAreStraight && preservedShape == RECTANGLE)
        {
            return true;
        }
        else if (preservedShape == QUADRANGLE)
        {
            return true;
        }
    }
    return false;
}

bool ShapeFilter::isHalfCircle(std::vector<cv::Point> contour)
{
    cv::RotatedRect rectangle = cv::minAreaRect(contour);
    cv::Point2f corners[4];
    rectangle.points(corners);
    double area = cv::norm(corners[0] - corners[1]) * cv::norm(corners[1] - corners[2]);
    double contourArea = cv::contourArea(contour);

    if (contourArea / area > M_PI / 4 - MAXIMUM_DEVIATION && contourArea / area < M_PI / 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double ShapeFilter::calculateAngle(cv::Point point1, cv::Point point2, cv::Point point3)
{
    double angle1 = std::atan2(point1.x - point2.x, point1.y - point2.y);
    double angle2 = std::atan2(point3.x - point2.x, point3.y - point2.y);
    double diff = angle2 - angle1;
    if (diff > M_PI)
        diff -= M_PI;
    else if (diff < -M_PI)
        diff += M_PI;
    diff *= STRAIGHT_ANGLE / M_PI;
    return abs(diff);
}

double ShapeFilter::calculateDistance(cv::Point point1, cv::Point point2)
{
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

cv::Mat ShapeFilter::removeSmallContours(cv::Mat inputMat, std::vector<std::vector<cv::Point>> contours)
{
    std::vector<std::vector<cv::Point>> smallContours;

    for (size_t i = 0; i < contours.size(); ++i)
    {
        if (cv::contourArea(contours[i]) < MINIMUM_CONTOUR_SIZE)
        {
            smallContours.push_back(contours[i]);
        }
    }
    cv::drawContours(inputMat, smallContours, -1, cv::Scalar(0, 0, 0), 6);
    return inputMat;
}
