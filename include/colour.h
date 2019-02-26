#ifndef COLOUR_H
#define COLOUR_H

#include "colour_range.h"

const ColourRange YELLOW_COLOR_RANGE     = {cv::Scalar(20,65,100),   cv::Scalar(40,255,255)};
const ColourRange RED_LOW_COLOR_RANGE    = {cv::Scalar(0,50,50),    cv::Scalar(10,255,255)};
const ColourRange RED_HIGH_COLOR_RANGE   = {cv::Scalar(160,50,50),  cv::Scalar(180,255,255)};
const ColourRange GREEN_COLOR_RANGE      = {cv::Scalar(25,70,24),   cv::Scalar(90,255,130)};
const ColourRange BLUE_COLOR_RANGE       = {cv::Scalar(78,100,80),  cv::Scalar(133,255,250)};
const ColourRange BLACK_LOW_COLOR_RANGE  = {cv::Scalar(0,0,0),      cv::Scalar(180,255,50)};
const ColourRange BLACK_HIGH_COLOR_RANGE = {cv::Scalar(0,205,0),    cv::Scalar(180,255,58)};
const ColourRange WHITE_LOW_COLOR_RANGE  = {cv::Scalar(0,5,170),    cv::Scalar(180,100,255)};
const ColourRange WHITE_HIGH_COLOR_RANGE = {cv::Scalar(0,35,170),   cv::Scalar(180,60,255)};
const ColourRange WOOD_COLOR_RANGE       = {cv::Scalar(10,64,87), cv::Scalar(18,190,188)};


///Enum which represents the color of a specification
enum Colour
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    WOOD
};



#endif // COLOUR_H