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

cv::Mat ShapeFilter::preserveShape(cv::Mat inputMat, Shape preservedShape)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(inputMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    inputMat = removeSmallContours(inputMat, contours);
    for (int i = 0; i < contours.size(); ++i)
    {
        bool allAnglesAreStraight = true;
        std::vector<cv::Point> approx;
        approxPolyDP(contours[i], approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.05, true);
        switch (preservedShape)
        {
        case RECTANGLE:
        case SQUARE:
        case QUADRANGLE:
            if (approx.size() == 4)
            {
                if (isShape(contours[i], approx, preservedShape))
                {
                    foundContours.push_back(contours[i]);
                }
            }
            break;
        case CIRCLE:
            std::cout << "Not implemented" << std::endl;
            break;
        case TRIANGLE:
            if (approx.size() == 3)
            {
                foundContours.push_back(contours[i]);
            }
            break;
        case HALF_CIRCLE:
            if (isHalfCircle(contours[i]))
            {
                foundContours.push_back(contours[i]);
            }
            break;
        }
    }
    cv::cvtColor(inputMat, inputMat, cv::COLOR_GRAY2BGR);
    cv::drawContours(inputMat, foundContours, -1, cv::Scalar(255, 0, 0), 6, 6);
    return inputMat;
}
bool ShapeFilter::isTriangle(cv::Mat inputMat)
{
}

bool ShapeFilter::isShape(std::vector<cv::Point> contour, std::vector<cv::Point> approx, Shape preservedShape)
{
    float length1, length2, length3, length4;
    bool allAnglesAreStraight;
    for (int i = 0; i < 4; ++i)
    {
        float angle = calculateAngle(approx[(0 + i) % 4], approx[(1 + i) % 4], approx[(2 + i) % 4]);

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
            if (abs(length1 - length2 < LENGTH_DEVIATION) || abs(length3 - length4 < LENGTH_DEVIATION))
            {
                float sidesLength = ((float)calculateDistance(approx[0], approx[1]) + (float)calculateDistance(approx[1], approx[2]) + (float)calculateDistance(approx[2], approx[3]) + (float)calculateDistance(approx[3], approx[0])) / 4;
                float surface = pow(sidesLength, 2);
                std::cout << "Square found at position: (" << approx[0].x << "-" << approx[0].y << ") (" << approx[1].x << "-" << approx[1].y << ") (" << approx[2].x << "-" << approx[2].y << ") (" << approx[3].x << "-" << approx[3].y << ") it's sides are: " << sidesLength << " pixels long and it has a surface of: " << surface << " pixels" << std::endl;
                return true;
            }
        }
        else if (allAnglesAreStraight && preservedShape == RECTANGLE)
        {
            float sides1Length = ((float)calculateDistance(approx[0], approx[1]) + (float)calculateDistance(approx[2], approx[3])) / 2;
            float sides2Length = ((float)calculateDistance(approx[1], approx[2]) + (float)calculateDistance(approx[3], approx[0])) / 2;
            float surface = sides1Length * sides2Length;
            std::cout << "Rectangle found at position: (" << approx[0].x << "-" << approx[0].y << ") (" << approx[1].x << "-" << approx[1].y << ") (" << approx[2].x << "-" << approx[2].y << ") (" << approx[3].x << "-" << approx[3].y << ") sides1 are: " << sides1Length << " pixels long and sides2 are: " << sides2Length << " pixels long it has a surface of: " << surface << " pixels" << std::endl;
            return true;
        }
        else
        {
            return true;
        }
    }
}

bool ShapeFilter::isHalfCircle(std::vector<cv::Point> contour)
{
    cv::RotatedRect rectangle = cv::minAreaRect(contour);
    cv::Point2f corners[4];
    rectangle.points(corners);
    double length = cv::norm(corners[0] - corners[1]);
    double width = cv::norm(corners[1] - corners[2]);
    double area = length * width;
    double contourArea = cv::contourArea(contour);

    if (contourArea / area > M_PI / 4 - MAXIMUM_DEVIATION && contourArea / area < M_PI / 4)
    {
        return true;
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

    for (int i = 0; i < contours.size(); ++i)
    {
        if (cv::contourArea(contours[i]) < MINIMUM_CONTOUR_SIZE)
        {
            smallContours.push_back(contours[i]);
        }
    }
    cv::drawContours(inputMat, smallContours, -1, cv::Scalar(0, 0, 0), 6);
    return inputMat;
}
