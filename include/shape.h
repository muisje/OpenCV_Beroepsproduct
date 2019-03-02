/**
 * @file shape.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief All the supported shapes
 * @version 0.2
 * @date 2019-03-02
 * 
 */
#ifndef SHAPE_H
#define SHAPE_H

#include "opencv2/core.hpp"

/**
 * @brief representation of shapes as enum
 * 
 */
enum Shape
{
    RECTANGLE,
    SQUARE,
    QUADRANGLE,
    TRIANGLE,
    CIRCLE,
    HALF_CIRCLE,
    NO_SHAPE,
    UNKNOWN_SHAPE
};


#endif // SHAPE_H