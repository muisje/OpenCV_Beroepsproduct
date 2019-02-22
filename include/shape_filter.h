#ifndef SHAPE_FILTER_H
#define SHAPE_FILTER_H

#include "detailed_shape.h"
#include "opencv2/core.hpp"
#define ANGLE_DEVIATION 10
#define LENGTH_DEVIATION 5
#define RIGHT_ANGLE 90
#define STRAIGHT_ANGLE 180
#define MINIMUM_LENGTH 20
#define MAXIMUM_DEVIATION 0.08
#define CIRCUMFERENCE_DEVIATION 10
#define MINIMUM_CONTOUR_SIZE 100

/**
 * @class ShapeFilter
 *
 * @brief ShapeFilter is a class which is able to 
 * 
 * This class can be used to add user interface elements to the generated Userinterface it
 * can also be used to connect SIGNALs from the generated userinterface to new SLOTS.  
 * 
 * @author Martijn Vogelaar
 * 
 * @date 18-10-2018
 * 
 */

class ShapeFilter
{

public:
  /**
    * @brief Construct a new Shape Filter object
    * 
    */
  ShapeFilter();
  /**
    * @brief Destroy the Shape Filter object
    * 
    */
  ~ShapeFilter();

  /**
    * @brief 
    * 
    * @param inputMat 
    * @param preservedShape 
    * @return cv::Mat 
    */
  cv::Mat preserveShape(cv::Mat inputMat, Shape preservedShape);

protected:
private:
  std::vector<std::vector<cv::Point>> foundContours;
  std::vector<DetailedShape> foundShape;
  bool isShape(std::vector<cv::Point> contour,  std::vector<cv::Point> approx, Shape preservedShape);
  bool isHalfCircle(std::vector<cv::Point> contour);
  bool isTriangle(cv::Mat inputMat);
  cv::Mat removeSmallContours(cv::Mat inputMat, std::vector<std::vector<cv::Point>> contours);
  double calculateAngle(cv::Point point1, cv::Point point2, cv::Point point3);
  double calculateDistance(cv::Point point1, cv::Point point2);
};

#endif //SHAPE_FILTER_H