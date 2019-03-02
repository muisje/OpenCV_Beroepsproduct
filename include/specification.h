/**
 * @file specification.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief eases handling of specifications (shape and colour).  
 * @version 0.2
 * @date 2019-03-02
 * 
 */

#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include "shape.h"
#include "colour.h"
#include "language.h"

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

bool operator!=(const Specification& lhs, const Specification& rhs);
/**
 * @brief Function to easily parse a specification
 * 
 * @param colour Character which will be "translated" to a Colour enum.
 * @param shape  Character which will be "translated" to a Shape enum.
 * @return Specification A specification will be returned. If the character was unkown the default return will be: RED,RECTANGLE
 */
Specification parseSpecification(std::string& colour, std::string& shape);

/**
 * @brief get the specification data as a string. 
 * 
 * @param specification the specification that needs to be converted.
 * @param language the language you want to be the specification represented in.
 * @return std::string the result.
 */
std::string specificationToString(Specification specification, Language language = Language::ENGLISH);

#endif // SPECIFICATION_H
