#ifndef DETAILEDSHAPE_H
#define DETAILEDSHAPE_H

#include "opencv2/core.hpp"
#include "../include/specification.h"

/**
 * @class Shape
 *
 * @brief Struct to store properties of a shape in
 * 
 * This struct is meant to make it easier to store the properties of shapes which have been found in
 * 
 * @author Martijn Vogelaar
 * 
 * @date 13-2-2019
 * 
 */
class DetailedShape
{
public:
  DetailedShape(std::vector<cv::Point> contour, Specification specification);
  ~DetailedShape();

private:
  std::vector<cv::Point> contour;
  Specification specification;
  cv::Point middlepoint;
  double surface;
};

#endif // DETAILEDSHAPE_H