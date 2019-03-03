/**
 * @file detection.h
 * @author Maurits Muijsert (MPW.Muijsert@student.han.nl), Martijn Vogelaar
 * @brief function that wrap detection and drawin.
 * @version 0.1
 * @date 2019-03-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef DETECTION_H
#define DETECTION_H
#include "language.h"
#include "specification.h"
#include <opencv2/opencv.hpp>
#include <atomic>
#include <string>

using namespace cv;
#define COORDINATE_DEVIATION 80


/**
 * @brief detect and draw
 * 
 */
class Detection
{
private:
  Detection();
  ~Detection();

  static void detectAndDrawOnce(cv::Mat image, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, Language language);
public:

  /**
   * @brief detects and draws on a live image from the webcam
   * 
   * @param exitProgram a variable used to know if the program needs to stop.
   * @param spec the specification which to detect.
   * @param camera which is used for getting the live images
   */
  static void detectAndDrawLive(std::atomic<bool>* exitProgram,std::atomic<Specification>* spec, short camera);

  /**
   * @brief detects and draws on a static image from a file
   * 
   * @param exitProgram 
   * @param spec a variable used to know if the program needs to stop.
   * @param needToPrint status if it is needed to print
   * @param imageFileName the name of the desired image.
   * @param language the language the feedback is printed in.
   */
  static void detectAndDrawStatic(std::atomic<bool>* exitProgram, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, const std::string & imageFileName, Language language);

};

#endif