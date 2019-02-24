#ifndef COLOURED_SHAPE_FINDER_H
#define COLOURED_SHAPE_FINDER_H

#include "specification.h"
#include "detailed_shape.h"
#include "colour.h"

#include <opencv2/opencv.hpp>

class ColouredShapeFinder
{
private:
    /* data */
    ColouredShapeFinder(/* args */);
    ~ColouredShapeFinder();
public:

    static std::vector<DetailedShape> find(cv::Mat image, Specification spec);
    static std::vector<cv::Vec3f> findCircles(cv::Mat image, enum::Colour colour);
};



#endif // COLOURED_SHAPE_FINDER_H