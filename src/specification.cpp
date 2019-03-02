#include "../include/specification.h"
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/assert.hpp> 
#include <map>
#include <iostream>

const std::map<std::string, Shape> stringToShapeEnglish = boost::assign::list_of<std::pair<std::string, Shape> > 
    ("RECTANGLE", Shape::RECTANGLE) ("TRIANGLE", Shape::TRIANGLE) ("HALF_CIRCLE", Shape::HALF_CIRCLE) 
    ("SQUARE", Shape::SQUARE) ("CIRCLE", Shape::CIRCLE);

const std::map<std::string, Colour> stringToColourEnglish = boost::assign::list_of<std::pair<std::string, Colour> >
    ("RED", Colour::RED) ("GREEN", Colour::GREEN) ("BLUE", Colour::BLUE) ("YELLOW", Colour::YELLOW) 
    ("WOOD", Colour::WOOD);

std::map<Shape, std::string> shapeToStringEnglish;
std::map<Colour, std::string> colourToStringEnglish;


std::string shapeToString(enum::Shape shape)
{
    if (shapeToStringEnglish.size() != stringToShapeEnglish.size())
    {
        for(auto it = stringToShapeEnglish.begin(); it != stringToShapeEnglish.end(); it++)
        {
        shapeToStringEnglish[it->second] = it->first;
        }
    }
    auto iterator = shapeToStringEnglish.find(shape);
    if (iterator == shapeToStringEnglish.end())
    {
        return "UNKNOWN_SHAPE";
    }
    return iterator->second;
}

std::string colourToString(enum::Colour colour)
{
    if (colourToStringEnglish.size() != stringToColourEnglish.size())
    {
        for(auto it = stringToColourEnglish.begin(); it != stringToColourEnglish.end(); it++)
        {
        colourToStringEnglish[it->second] = it->first;
        }
    }
    auto iterator = colourToStringEnglish.find(colour);
    if (iterator == colourToStringEnglish.end())
    {
        return "UNKNOWN_COLOUR";
    }
    return iterator->second;
}

std::string specificationToString(Specification specification, Language language)
{
    std::string shape = shapeToString(specification.shape);
    std::string colour = colourToString(specification.colour);

    if (language == Language::DUTCH)
    {
        shape = toDutch(shape);
        colour = toDutch(colour);
    }

    return shape + " " + colour;
}

Shape findShapeEnum(std::string &shape)
{
    auto iterator = stringToShapeEnglish.find(shape);
    if (iterator == stringToShapeEnglish.end())
    {
        return Shape::UNKNOWN_SHAPE;
    }
    return iterator->second;
}

Colour findColourEnum(std::string &colour)
{
    auto iterator = stringToColourEnglish.find(colour);
    if (iterator == stringToColourEnglish.end())
    {
        return Colour::UNKNOWN_COLOUR;
    }
    return iterator->second;
}

Specification parseSpecification(std::string &shape, std::string &colour)
{
    std::transform(colour.begin(), colour.end(), colour.begin(), ::toupper);
    std::transform(shape.begin(), shape.end(), shape.begin(), ::toupper);
    
    return Specification{findShapeEnum(shape), findColourEnum(colour)};
}

bool operator!=(const Specification &lhs, const Specification &rhs)
{
    return lhs.colour != rhs.colour || lhs.shape != rhs.shape;
}