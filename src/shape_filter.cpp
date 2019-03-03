#include "../include/shape_filter.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

ShapeFilter::ShapeFilter()
{
}

ShapeFilter::~ShapeFilter()
{
}

bool ShapeFilter::isShape(const std::vector<cv::Point> approx, Shape preservedShape)
{
    std::vector<float> lengths;
    bool allAnglesAreStraight = true;
    for (int i = 0; i < 4; ++i)
    {
        double angle = calculateAngle(approx[(0 + i) % 4], approx[(1 + i) % 4], approx[(2 + i) % 4]);

        if (angle > RIGHT_ANGLE + ANGLE_DEVIATION || angle < RIGHT_ANGLE - ANGLE_DEVIATION)
        {
            allAnglesAreStraight = false;
            i = 5;
        }
    }

    lengths.push_back((float)calculateDistance(approx[0], approx[1]));
    lengths.push_back((float)calculateDistance(approx[1], approx[2]));
    lengths.push_back((float)calculateDistance(approx[2], approx[3]));
    lengths.push_back((float)calculateDistance(approx[3], approx[0]));
    lengths.push_back((float)calculateDistance(approx[3], approx[1]));
    lengths.push_back((float)calculateDistance(approx[2], approx[0]));
    std::sort(lengths.begin(), lengths.end(), std::greater<float>());

    if (lengths[lengths.size() - 1] > MINIMUM_LENGTH)
    {
        if (allAnglesAreStraight && preservedShape == SQUARE)
        {
            if (abs((lengths[3] - lengths[2]) * 100) / lengths[2] < LENGTH_DEVIATION && abs((lengths[4] - lengths[3]) * 100) / lengths[4] < LENGTH_DEVIATION)
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
    double height = cv::norm(corners[0] - corners[1]);
    double width = cv::norm(corners[1] - corners[2]);
    double area = height * width;
    double contourArea = cv::contourArea(contour);

    if (contourArea / area > M_PI / 4 - MAXIMUM_DEVIATION && contourArea / area < M_PI / 4)
    {
        //If the width and height of the minAreaRect is close to zero it is a square.
        //Since the previous if statement is both true with circles as half circles
        //circles need to be filtered out. If the contour is a circle the minAreaRect
        //is a rectangle of which the height as length are close to eachother.
        if (abs(height - width) < LENGTH_DEVIATION)
        {
            return false;
        }
        else if (
            ((height / width > 0.35 && height / width < 0.60) || (width / height > 0.40 && width / height < 0.6)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return false;
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

cv::Mat ShapeFilter::removeSmallContours(cv::Mat inputMat)
{
    std::vector<std::vector<cv::Point>> smallContours;
    std::vector<DetailedShape> detailedShapes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(inputMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

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
