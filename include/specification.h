#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "shape.h"
#include "colour.h"

/**
 * @struct Specification
 *
 * @brief Struct to store a specifications data in
 * 
 * This struct is meant to make it easier to store specification data
 * 
 * @author Martijn Vogelaar
 * 
 * @date 13-2-2019
 * 
 */

struct Specification
{
    Shape shape;
    Colour colour;
};

Specification parseSpecification(char colour, char shape);

#endif // SPECIFICATION_H
