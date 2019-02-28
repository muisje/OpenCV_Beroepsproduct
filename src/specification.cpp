#include "../include/specification.h"
#include <iostream>
Specification parseSpecification(std::string &shape, std::string &colour)
{
    Shape finalShape;
    Colour finalColour;
    std::transform(colour.begin(), colour.end(), colour.begin(), ::toupper);
    std::transform(shape.begin(), shape.end(), shape.begin(), ::toupper);
    if (shape == "RECTANGLE")
    {
        finalShape = RECTANGLE;
    }
    else if (shape == "SQUARE")
    {
        finalShape = SQUARE;
    }
    else if (shape == "TRIANGLE")
    {
        finalShape = TRIANGLE;
    }
    else if (shape == "HALF_CIRCLE")
    {
        finalShape = HALF_CIRCLE;
    }
    else if (shape == "CIRCLE")
    {
        finalShape = CIRCLE;
    }
    else
    {
        finalShape = UNKNOWN_SHAPE;
    };

    if (colour == "RED")
    {
        finalColour = RED;
    }
    else if (colour == "GREEN")
    {
        finalColour = GREEN;
    }
    else if (colour == "BLUE")
    {
        finalColour = BLUE;
    }
    else if (colour == "YELLOW")
    {
        finalColour = YELLOW;
    }
    else if (colour == "WOOD")
    {
        finalColour = WOOD;
    }
    else
    {
        finalColour = UNKNOWN_COLOUR;
    }
    return Specification{finalShape, finalColour};
}

bool operator!=(const Specification &lhs, const Specification &rhs)
{
    return lhs.colour != rhs.colour || lhs.shape != rhs.shape;
}