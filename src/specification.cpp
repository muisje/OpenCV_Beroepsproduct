#include "../include/specification.h"
#include <iostream>
Specification parseSpecification(char colour, char shape)
{
    Shape finalShape;
    Colour finalColour;
    switch (shape)
    {
    case 'r':
    case 'R':
        finalShape = RECTANGLE;
        break;
    case 's':
    case 'S':
        finalShape = SQUARE;
        break;
    case 'h':
    case 'H':
        finalShape = HALF_CIRCLE;
        break;
    case 'c':
    case 'C':
        finalShape = CIRCLE;
        break;
    case 't':
    case 'T':
        finalShape = TRIANGLE;
        break;
    default:
        finalShape = RECTANGLE;
        break;
    };

    switch (colour)
    {
    case 'r':
    case 'R':
        finalColour = RED;
        break;
    case 'b':
    case 'B':
        finalColour = BLUE;
        break;
    case 'y':
    case 'Y':
        finalColour = YELLOW;
        break;
    case 'g':
    case 'G':
        finalColour = GREEN;
        break;
    case 'w':
    case 'W':
        finalColour = WOOD;
        break;
    default:
        finalColour = RED;
        break;
    };
    return Specification{finalShape, finalColour};
}