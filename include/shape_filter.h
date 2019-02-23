#ifndef SHAPE_FILTER_H
#define SHAPE_FILTER_H

#include "detailed_shape.h"
#include "../include/colour.h"
#include "../include/specification.h"
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
    * @brief This function will only preserve the given shape if one is in the given Matrix
    * 
    * @param inputMat The shape will be searched in this matrix.
    * @param preservedShape The shape which will be searched for in the matrix.
    * @return cv::Mat The image returned will have the given shape highlighted.
    */
  cv::Mat preserveShape(cv::Mat inputMat, Specification specification);

protected:
private:
  std::vector<std::vector<cv::Point>> foundContours;
  std::vector<DetailedShape> foundShape;

  /**
   * @brief 
   * 
   * @param approx 
   * @param preservedShape 
   * @return true 
   * @return false 
   */
  bool isShape(std::vector<cv::Point> approx, Shape preservedShape);

  /**
   * @brief This function returns wether the contour which is supplied is a half circle 
   * 
   * @param contour This is the contour which will be looked at to see wether it is a half circle or not.
   * @return true True is being returned if the supplied contour is a half circle
   * @return false False is being returned if the supplied contour is not a half circle
   */
  bool isHalfCircle(std::vector<cv::Point> contour);
  
  /**
   * @brief This function will remove all contours which are of an insufficient surface.
   * 
   * @param inputMat Contours which are to small will be removed from this matrix.
   * @param contours Contours which are in the given matrix.
   * @return cv::Mat A matrix will be returned in which the contours which are of an insufficient surface are removed
   */
  cv::Mat removeSmallContours(cv::Mat inputMat, std::vector<std::vector<cv::Point>> contours);
  
  /**
   * @brief Calculate the angle between 3 given points
   * 
   * @detail The angle of "point 2" will be calculated.
   * 
   * @param point1 First point from which the angle will be calculated.
   * @param point2 Second point from which the angle will be calculated.
   * @param point3 Third point from which the angle will be calculated.
   * @return double The angle will be returned
   */
  double calculateAngle(cv::Point point1, cv::Point point2, cv::Point point3);
  
  /**
   * @brief Calculate the distance between two points.
   * 
   * @param point1 First point from which the distance will be calculated.
   * @param point2 Second point from which the distance will be calculated.
   * @return double Distance between the two points will be calcaluated.
   */
  double calculateDistance(cv::Point point1, cv::Point point2);
};

#endif //SHAPE_FILTER_H