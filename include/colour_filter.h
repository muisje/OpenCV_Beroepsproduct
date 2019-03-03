/**
 * @file colour_filter.h
 * @author Martijn Vogelaar
 * @brief filtering colours on a image.
 * @version 0.1
 * @date 2019-03-02
 * 
 */
#ifndef COLOURFILTER_H
#define COLOURFILTER_H

#include "colour.h"
#include "opencv2/core.hpp"

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
  static cv::Mat preserveColour(cv::Mat inputMat, Colour preservedColour);

protected:
  /**
   * @brief Construct a new Colour Filter object
   * 
   */
  ColourFilter();
  /**
   * @brief Destroy the Colour Filter object
   * 
   */
  ~ColourFilter();

private:
};

#endif //COLOURFILTER_H