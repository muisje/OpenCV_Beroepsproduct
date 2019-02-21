#ifndef COLOUR_H
#define COLOUR_H

#include "colour_range.h"

const ColourRange YELLOW_COLOR_RANGE     = {cv::Scalar(20,65,100),   cv::Scalar(40,255,255)};
const ColourRange RED_LOW_COLOR_RANGE    = {cv::Scalar(0,100,100),    cv::Scalar(10,255,255)};
const ColourRange RED_HIGH_COLOR_RANGE   = {cv::Scalar(160,100,130),  cv::Scalar(179,255,255)};
const ColourRange GREEN_COLOR_RANGE      = {cv::Scalar(25,126,24),   cv::Scalar(92,255,130)};
const ColourRange BLUE_COLOR_RANGE       = {cv::Scalar(100,125,25),  cv::Scalar(140,255,140)};
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