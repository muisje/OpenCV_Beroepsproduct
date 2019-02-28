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

    static void drawNotFound(cv::InputOutputArray image);
    static void drawInfo(cv::InputOutputArray image, cv::Point center, double area, double ticks, int yOffset = 0);
    
public:
    static void draw(cv::InputOutputArray image, std::vector<DetailedShape> detailedShapes);
    static void draw(cv::InputOutputArray image, std::vector<cv::Vec3f> circles);

};



#endif