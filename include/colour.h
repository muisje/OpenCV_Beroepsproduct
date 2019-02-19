#ifndef COLOUR_H
#define COLOUR_H

#include "colour_range.h"

const ColourRange YELLOW_COLOR_RANGE     = {cv::Scalar(20,78,20),   cv::Scalar(37,255,255)};
const ColourRange RED_LOW_COLOR_RANGE    = {cv::Scalar(0,50,50),    cv::Scalar(10,255,255)};
const ColourRange RED_HIGH_COLOR_RANGE   = {cv::Scalar(160,50,50),  cv::Scalar(180,255,255)};
const ColourRange GREEN_COLOR_RANGE      = {cv::Scalar(36,70,30),   cv::Scalar(78,255,255)};
const ColourRange BLUE_COLOR_RANGE       = {cv::Scalar(80,30,0),  cv::Scalar(140,255,255)};
const ColourRange BLACK_LOW_COLOR_RANGE  = {cv::Scalar(0,0,0),      cv::Scalar(180,255,50)};
const ColourRange BLACK_HIGH_COLOR_RANGE = {cv::Scalar(0,205,0),    cv::Scalar(180,255,58)};
const ColourRange WHITE_LOW_COLOR_RANGE  = {cv::Scalar(0,5,170),    cv::Scalar(180,100,255)};
const ColourRange WHITE_HIGH_COLOR_RANGE = {cv::Scalar(0,35,170),   cv::Scalar(180,60,255)};


///Enum which represents the color of a specification
enum Colour
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE
};



#endif // COLOUR_H