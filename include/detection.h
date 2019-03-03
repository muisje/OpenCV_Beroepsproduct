#ifndef DETECTION_H
#define DETECTION_H
#include <opencv2/opencv.hpp>
#include <atomic>
#include "language.h"
#include "specification.h"
using namespace cv;
#define COORDINATE_DEVIATION 80


/**
 * @brief Class to make printing certain data to the console easier.
 * 
 */

class Detection
{
private:
  Detection();
  ~Detection();


public:
  static void detectAndDrawOnce(cv::Mat image, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, Language language);

  static void detectAndDrawLive(std::atomic<bool>* exitProgram,std::atomic<Specification>* spec);

  static void detectAndDrawStatic(std::atomic<bool>* exitProgram, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, Language language);

  static void detectAndDraw(bool live,std::atomic<bool>* exitProgram, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, Language language);
};

#endif