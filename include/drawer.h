/**
 * @file drawer.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief class for drawing on images. 
 * @version 0.2
 * @date 2019-03-02
 * 
 */

#ifndef DRAWER_H
#define DRAWER_H

#include "detailed_shape.h"
#include <opencv2/opencv.hpp>
#define TEXT_RED 0
#define TEXT_GREEN 255
#define TEXT_BLUE 120

class Drawer
{
private:
  Drawer(/* args */);
  ~Drawer();
  /**
     * @brief Function to easily draw text on a given input image
     * 
     * @param image Image on which the text will be drawn on.
     * @param inputText Text which will be drawn on the image.
     */
  static void drawText(cv::InputOutputArray image, std::string inputText);
  /**
     * @brief Function which makes it easier to draw info about a DetailedShape
     * 
     * @details The drawInfo function makes it easier to display information about a shape on an image.
     * The following information can be drawn on the image: CenterPoint, Surface and Amount of ticks.
     * 
     * @param image Image on which the information will be drawn on.
     * @param center Centerpoint of the shape to be able to draw the coordinates and draw the actual middle point.
     * @param area Area of the shape to be able to draw this on the given image.
     * @param ticks Time it took to determine that the shape was here. THis will also be drawn on the image.
     * @param yOffset 
     */
  static void drawInfo(cv::InputOutputArray image, cv::Point center, double area, int yOffset = 0);

public:
  /**
     * @brief Function which will handle the drawing of Detailed shapes
     * 
     * @details The draw function will handle the drawing of detailed shapes. It will highlight the contour of the shape
     * and also draw information about each shape on the image.
     * 
     * @param image Image on which the shapes and information about shapes will be drawn.
     * @param detailedShapes Shapes will be drawn on the image.
     * @param specification The current specification is needed to determine wether no shape was found
     * because there was no shape or the input was incorrect.
     */
  static void draw(cv::InputOutputArray image, std::vector<DetailedShape> detailedShapes, Specification specification, std::clock_t duration);

  /**
     * @brief Function which will handle the drawing of Detailed shapes
     * 
     * @details The draw function will handle the drawing of detailed shapes. It will highlight the contour of the shape
     * and also draw information about each shape on the image.
     * @param circles
     * @param specification The current specification is needed to determine wether no shape was found
     * because there was no shape or the input was incorrect.
     */
  static void draw(cv::InputOutputArray image, std::vector<cv::Vec3f> circles, Specification specification, std::clock_t duration);

  static void draw(cv::InputOutputArray image, Specification specification);

  static void drawTime(cv::InputOutputArray image, std::clock_t duration);
};

#endif