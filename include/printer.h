/**
 * @file printer.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl)
 * @brief printing data to console
 * @version 0.1
 * @date 2019-03-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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
    /**
     * @brief prints the text of not found to console
     * 
     */
    static void printNotFound(std::clock_t duration);
    /**
     * @brief prints the data of circles to console
     * 
     * @param circles to be printed
     */
    static void print(std::vector<cv::Vec3f> &circles, std::clock_t duration);
    /**
     * @brief every other shape then circle to be printed to console
     * 
     * @param shapes to be printed
     */
    static void print(std::vector<DetailedShape> &shapes, std::clock_t duration);

    /**
     * @brief 
     * 
     * @param batchNumber 
     */
    static void printUnknown(int batchNumber);

    /**
     * @brief 
     * 
     */
    static void print(std::string);
};

#endif