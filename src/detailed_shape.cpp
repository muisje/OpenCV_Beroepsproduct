#include "../include/detailed_shape.h"
#include <opencv/cv.hpp>
DetailedShape::DetailedShape(std::vector<cv::Point> contour, Specification specification):contour(contour), specification(specification)
{
    cv::Moments moment = cv::moments(contour, false);
    middlepoint.x = int(moment.m10 / moment.m00);
    middlepoint.y = int(moment.m01 / moment.m00);
    surface = cv::contourArea(contour);
}

DetailedShape::~DetailedShape()
{
}