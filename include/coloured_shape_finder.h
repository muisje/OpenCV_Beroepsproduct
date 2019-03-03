/**
 * @file coloured_shape_finder.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief class that combines finding shapes and colours to find a coloured shape. 
 * @version 0.2
 * @date 2019-03-02
 * 
 */
#ifndef COLOURED_SHAPE_FINDER_H
#define COLOURED_SHAPE_FINDER_H

#include "specification.h"
#include "detailed_shape.h"
#include "colour.h"

#include <opencv2/opencv.hpp>

#define MINIMUM_SURFACE 100

/**
 * @brief class that combines finding shapes and colours to find a coloured shape. 
 * 
 */
class ColouredShapeFinder
{
private:
    /* data */
    ColouredShapeFinder(/* args */);
    ~ColouredShapeFinder();
public:
    /**
     * @brief find a coloured shape thats not a circle at the given image.
     * 
     * @param image where you want to find your coloured shape.
     * @param spec the specification of the shape you want to find.
     * @return std::vector<DetailedShape> a list of found shapes as detailed shapes.
     */
    static std::vector<DetailedShape> find(cv::Mat image, Specification spec);
    /**
     * @brief finds coloured circles at the given image.
     * 
     * @param image image where you want to find your coloured shape.
     * @param colour the colour of the circle you want to find
     * @return std::vector<cv::Vec3f>  list of found circles.
     */
    static std::vector<cv::Vec3f> findCircles(cv::Mat image, enum::Colour colour);
};

#endif // COLOURED_SHAPE_FINDER_H