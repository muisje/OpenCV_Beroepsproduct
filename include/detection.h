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

  static void detectAndDrawLive(std::atomic<bool>* exitProgram,std::atomic<Specification>* spec, short camera);

  static void detectAndDrawStatic(std::atomic<bool>* exitProgram, std::atomic<Specification>* spec, std::atomic<bool>* needToPrint, const std::string & imageFileName, Language language);

};

#endif