/**
 * @file colour.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief the definition of colours
 * @version 0.1
 * @date 2019-03-02
 * 
 * 
 */
#ifndef COLOUR_H
#define COLOUR_H

#include "colour_range.h"
/// @brief Colour range in which yellow is located
const ColourRange YELLOW_COLOR_RANGE     = {cv::Scalar(21,100,0),   cv::Scalar(40,255,255)}; // HLOW 20

///@brief Colour range 1 out of 2 in which red is located 
const ColourRange RED_LOW_COLOR_RANGE    = {cv::Scalar(0,61,0),    cv::Scalar(12,255,255)};

///@brief Colour range 2 out of 2 in which red is located 
const ColourRange RED_HIGH_COLOR_RANGE   = {cv::Scalar(144,50,0),  cv::Scalar(180,255,255)};

///@brief Colour range 1 out of 2 in which green is located 
const ColourRange GREEN_COLOR_RANGE_LOW  = {cv::Scalar(25,45,24),   cv::Scalar(90,255,130)};

///@brief Colour range 2 out of 2 in which green is located 
const ColourRange GREEN_COLOR_RANGE_HIGH = {cv::Scalar(50,45,24),   cv::Scalar(90,255,255)};

///@brief Colour range in which blue is located 
const ColourRange BLUE_COLOR_RANGE       = {cv::Scalar(87,42,0),  cv::Scalar(151,255,255)};

///@brief Colour range 1 out of 2 in which black is located 
const ColourRange BLACK_LOW_COLOR_RANGE  = {cv::Scalar(0,0,0),      cv::Scalar(180,255,50)};

///@brief Colour range 2 out of 2 in which black is located 
const ColourRange BLACK_HIGH_COLOR_RANGE = {cv::Scalar(0,205,0),    cv::Scalar(180,255,58)};

///@brief Colour range 1 out of 2 in which white is located 
const ColourRange WHITE_LOW_COLOR_RANGE  = {cv::Scalar(0,5,170),    cv::Scalar(180,100,255)};

///@brief Colour range 2 out of 2 in which white is located 
const ColourRange WHITE_HIGH_COLOR_RANGE = {cv::Scalar(0,35,170),   cv::Scalar(180,60,255)};

///@brief Colour range in which wood is located 
const ColourRange WOOD_COLOR_RANGE       = {cv::Scalar(13,55,60), cv::Scalar(23,206,255)};

///Enum which represents the color of a specification
enum Colour
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
    WHITE,
    WOOD,
    NO_COLOUR,
    UNKNOWN_COLOUR
};



#endif // COLOUR_H