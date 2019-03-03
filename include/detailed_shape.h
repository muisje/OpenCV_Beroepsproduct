/**
 * @file detailed_shape.h
 * @author Martijn Vogelaar
 * @brief class for storing detailed information about a shape
 * @version 0.1
 * @date 2019-03-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef DETAILEDSHAPE_H
#define DETAILEDSHAPE_H

#include "opencv2/core.hpp"
#include "../include/specification.h"

/**
 * @class DetailedShape
 *
 * @brief Class to store properties of a shape in
 * 
 * This class is meant to make it easier to store the properties of shapes which have been found in
 * 
 * @author Martijn Vogelaar
 * 
 * @date 13-2-2019
 * 
 */
class DetailedShape
{
public:
/**
 * @brief Construct a new Detailed Shape object
 * 
 */
  DetailedShape(std::vector<cv::Point> contour, Specification specification);
  /**
   * @brief Destroy the Detailed Shape object
   * 
   */
  ~DetailedShape();

// private:
  std::vector<cv::Point> contour;
  Specification specification;
  cv::Point middlepoint;
  double surface;
};

#endif // DETAILEDSHAPE_H