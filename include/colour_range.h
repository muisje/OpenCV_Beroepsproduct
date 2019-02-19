#ifndef COLOUR_RANGE_H
#define COLOUR_RANGE_H

#include "opencv2/core.hpp"

/**
 * @class ColourRange
 *
 * @brief Struct to ColourRanges in
 * 
 * This struct is meant to make it easier to store the low and high end of a colour in.
 * 
 * @author Martijn Vogelaar
 * 
 * @date 13-2-2019
 * 
 */

struct ColourRange {
    /**
     * @brief The lower end of the colour range
     * 
     */
    cv::Scalar colourLow;
    /**
     * @brief The higher end of the colour range
     * 
     */
    cv::Scalar colourHigh;
} ;



#endif // COLOUR_RANGE_H
