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
    std::vector<cv::Vec3f> circles;

    cv::Mat finalImage;
    cv::Mat tempImage;
    cv::Mat tempImage2;

    cv::Mat canny_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    switch (preservedShape)
    {
    case RECTANGLE:
        finalImage = findShape(inputMat, preservedShape, 4);
        break;
    case CIRCLE:
        cv::HoughCircles(inputMat, circles, CV_HOUGH_GRADIENT, 2, 20, 450, 60, 0, 100);
        cv::cvtColor(inputMat, finalImage, CV_GRAY2BGR);
        std::cout << "Amount of circles found: " << circles.size() << std::endl;
        for (int i = 0; i < circles.size(); ++i)
        {
            cv::circle(finalImage, cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(255, 0, 0), 4, 8, 0);
            std::cout << "Circle at position: x: " << circles[i][0] << " and y: " << circles[i][1] << " has a diameter of: " << circles[i][2] << " pixels, this circle has a surface of: " << M_PI * pow(circles[i][2], 2) << "pixels. " << std::endl;
        }
        break;
    case SQUARE:
        finalImage = findShape(inputMat, preservedShape, 4);
        break;
    case QUADRANGLE:
        finalImage = findShape(inputMat, preservedShape, 4);
        break;
    case TRIANGLE:
        finalImage = findShape(inputMat, preservedShape, 3);
        break;
    }
    return finalImage;
}

cv::Mat ShapeFilter::findShape(cv::Mat inputMat, Shape preservedShape, uint8_t approxSize)
{

    // cv::blur(inputMat, inputMat, cv::Size(3, 3), cv::Point(-1, -1), 1);
    cv::Mat_<int> kernel(5, 5);
    kernel << 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9;
    cv::morphologyEx(inputMat, inputMat, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(inputMat, inputMat, cv::MORPH_CLOSE, kernel);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> rightContours;
    std::vector<cv::Point> approx;

    cv::findContours(inputMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    for (int i = 0; i < contours.size(); ++i)
    {
        bool allAnglesAreStraight = true;
        approxPolyDP(contours[i], approx, cv::arcLength(contours[i], true) * 0.02, true);
        if (approx.size() == approxSize)
        {
            switch (preservedShape)
            {
            case RECTANGLE:
            case SQUARE:
                for (int i = 0; i < 4; ++i)
                {
                    float angle = calculateAngle(approx[(0 + i) % 4], approx[(1 + i) % 4], approx[(2 + i) % 4]);
                    std::cout << angle << std::endl;
                    if (angle > RIGHT_ANGLE + ANGLE_DEVIATION || angle < RIGHT_ANGLE - ANGLE_DEVIATION)
                    {
                        allAnglesAreStraight = false;
                        i = 5;
                    }
                }
                if (allAnglesAreStraight && preservedShape == SQUARE)
                {
                    if (abs((float)calculateDistance(approx[0], approx[1]) - (float)calculateDistance(approx[1], approx[2])) < LENGTH_DEVIATION)
                    {
                        if (abs((float)calculateDistance(approx[2], approx[3]) - (float)calculateDistance(approx[3], approx[0])) < LENGTH_DEVIATION)
                        {
                            float sidesLength = ((float)calculateDistance(approx[0], approx[1]) + (float)calculateDistance(approx[1], approx[2]) + (float)calculateDistance(approx[2], approx[3]) + (float)calculateDistance(approx[3], approx[0])) / 4;
                            float surface = pow(sidesLength, 2);
                            std::cout << "Square found at position: (" << approx[0].x << "-" << approx[0].y << ") (" << approx[1].x << "-" << approx[1].y << ") (" << approx[2].x << "-" << approx[2].y << ") (" << approx[3].x << "-" << approx[3].y << ") it's sides are: " << sidesLength << " pixels long and it has a surface of: " << surface << " pixels" << std::endl;
                            rightContours.push_back(contours[i]);
                        }
                    }
                }
                else if (allAnglesAreStraight && preservedShape == RECTANGLE)
                {
                    float sides1Length = ((float)calculateDistance(approx[0], approx[1]) + (float)calculateDistance(approx[2], approx[3])) / 2;
                    float sides2Length = ((float)calculateDistance(approx[1], approx[2]) + (float)calculateDistance(approx[3], approx[0])) / 2;
                    float surface = sides1Length * sides2Length;
                    std::cout << "Rectangle found at position: (" << approx[0].x << "-" << approx[0].y << ") (" << approx[1].x << "-" << approx[1].y << ") (" << approx[2].x << "-" << approx[2].y << ") (" << approx[3].x << "-" << approx[3].y << ") sides1 are: " << sides1Length << " pixels long and sides2 are: " << sides2Length << " pixels long it has a surface of: " << surface << " pixels" << std::endl;
                    rightContours.push_back(contours[i]);
                }
                break;

            default:
                rightContours.push_back(contours[i]);
                break;
            }
        }
    }
    cv::Mat tempImage;
    cv::cvtColor(inputMat, tempImage, cv::COLOR_GRAY2BGR);
    cv::drawContours(tempImage, rightContours, -1, cv::Scalar(0, 255, 0), 6);
    return tempImage;
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

//LAPLACE