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

/**
 * @brief Function to easily parse a specification
 * 
 * @param colour Character which will be "translated" to a Colour enum.
 * @param shape  Character which will be "translated" to a Shape enum.
 * @return Specification A specification will be returned. If the character was unkown the default return will be: RED,RECTANGLE
 */
Specification parseSpecification(char colour, char shape);

#endif // SPECIFICATION_H
