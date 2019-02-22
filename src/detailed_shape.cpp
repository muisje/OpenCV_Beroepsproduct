#include "../include/detailed_shape.h"
#include <opencv/cv.hpp>
#include <iostream>
DetailedShape::DetailedShape(Shape shape, std::vector<cv::Point> contour, Colour colour){
    cv::Moments mom = cv::moments(contour, false);
	cv::Point center(mom.m10/mom.m00, mom.m01/mom.m00);
    std::cout << "X: " << center.x << " y: " << center.y << std::endl;
}

DetailedShape::~DetailedShape(){

}