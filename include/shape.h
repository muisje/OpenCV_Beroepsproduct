#ifndef SHAPE_H
#define SHAPE_H

#include "opencv2/core.hpp"

///Enum which represents the shape of a specification
enum Shape
{
    RECTANGLE,
    SQUARE,
    QUADRANGLE,
    TRIANGLE,
    CIRCLE,
    HALF_CIRCLE,
    UNKNOWN_SHAPE
};


#endif // SHAPE_H