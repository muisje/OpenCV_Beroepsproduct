#include "../include/colour_filter.h"

ColourFilter::ColourFilter()
{
}
ColourFilter::~ColourFilter()
{
}

cv::Mat ColourFilter::preserveColour(cv::Mat inputMat, Colour preservedColour)
{
    cv::Mat outputMat1;
    cv::Mat outputMat2;
    cv::Mat finalOutputMat;
    switch (preservedColour)
    {
    case RED:
        inRange(inputMat, RED_LOW_COLOR_RANGE.colourLow, RED_LOW_COLOR_RANGE.colourHigh, outputMat1);
        inRange(inputMat, RED_HIGH_COLOR_RANGE.colourLow, RED_HIGH_COLOR_RANGE.colourHigh, outputMat2);
        finalOutputMat = outputMat1 | outputMat2;
        break;
    case YELLOW:
        inRange(inputMat, YELLOW_COLOR_RANGE.colourLow, YELLOW_COLOR_RANGE.colourHigh, finalOutputMat);
        break;
    case GREEN:
        inRange(inputMat, GREEN_COLOR_RANGE_LOW.colourLow, GREEN_COLOR_RANGE_LOW.colourHigh, outputMat1);
        inRange(inputMat, GREEN_COLOR_RANGE_HIGH.colourLow, GREEN_COLOR_RANGE_HIGH.colourHigh, outputMat2);
        finalOutputMat = outputMat1 | outputMat2;
        break;
    case BLUE:
        inRange(inputMat, BLUE_COLOR_RANGE.colourLow, BLUE_COLOR_RANGE.colourHigh, finalOutputMat);
        break;
    case BLACK:
        inRange(inputMat, BLACK_LOW_COLOR_RANGE.colourLow, BLACK_LOW_COLOR_RANGE.colourHigh, outputMat1);
        inRange(inputMat, BLACK_HIGH_COLOR_RANGE.colourLow, BLACK_HIGH_COLOR_RANGE.colourHigh, outputMat2);
        finalOutputMat = outputMat1 | outputMat2;
        break;
    case WHITE:
        inRange(inputMat, WHITE_LOW_COLOR_RANGE.colourLow, WHITE_LOW_COLOR_RANGE.colourHigh, outputMat1);
        inRange(inputMat, WHITE_HIGH_COLOR_RANGE.colourLow, WHITE_HIGH_COLOR_RANGE.colourHigh, outputMat2);
        finalOutputMat = outputMat1 | outputMat2;
        break;
    case WOOD:
        inRange(inputMat, WOOD_COLOR_RANGE.colourLow, WOOD_COLOR_RANGE.colourHigh, finalOutputMat);
        break;
    case UNKNOWN_COLOUR:
        inRange(inputMat, cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0), finalOutputMat);
        break;
    }
    return finalOutputMat;
}
