#ifndef COLOURFILTER_H
#define COLOURFILTER_H

#include "colour.h"
#include "opencv2/core.hpp"
#include "../include/colour.h"

/**
 * @class ColourFilter
 *
 * @brief ColourFilter is a class which is able to filter out all colours except the given colour.
 * 
 * 
 * @author Martijn Vogelaar
 * 
 * @date 18-10-2018
 * 
 */

class ColourFilter
{

public:
  ColourFilter();
  ~ColourFilter();

  /** @brief 
    *
  */

  /**
    * @brief The preserveColour function will filter out all colours except the given one.
    * @details The preserveCOlour function will filter out all colours except the given one
    * 
    * 
    * @param inputMat Input matrix from which the colours will be filtered. An HSV image should be given.
    * @param preservedColour Colour which should be preserved from the given matrix.
    * @return cv::Mat Matrix The function will return a Matrix which will only exist out of two
    * colours namely black and white. The white areas will be the places where the given colour
    *  was found. The black areas will
    */
  cv::Mat preserveColour(cv::Mat inputMat, Colour preservedColour);

protected:
private:
};

#endif //COLOURFILTER_H