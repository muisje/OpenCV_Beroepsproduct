#ifndef PRINTER_H
#define PRINTER_H


#include "detailed_shape.h"
#include <opencv2/opencv.hpp>

class Printer
{
private:
    Printer(/* args */);
    ~Printer();
public:
    static void printNotFound();
    static void print(std::vector<cv::Vec3f> circles);
    static void print(std::vector<DetailedShape> shapes);
};

#endif