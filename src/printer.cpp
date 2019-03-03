#include "../include/printer.h"
#include <vector>

void Printer::print(std::vector<cv::Vec3f>& circles, std::clock_t duration)
{
    for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
    {
        cv::Point center(static_cast<int>(std::round(circles[current_circle][0])), static_cast<int>(std::round(circles[current_circle][1])));
        int radius = static_cast<int>(std::round(circles[current_circle][2]));

        double area = M_PI * pow(radius, 2);
        std::cout << "(" << center.x << ", " << center.y << ") " << area << " px^2 " << std::to_string(duration) << " clock ticks" << std::endl;
    }
    std::cout << std::endl;
}

void Printer::print(std::vector<DetailedShape>& shapes, std::clock_t duration)
{
    for (DetailedShape shape : shapes)
    {
        std::cout << "(" << shape.middlepoint.x << ", " << shape.middlepoint.y << ") " << shape.surface << " px^2 " << std::to_string(duration) << " clock ticks" << std::endl;
    }
    std::cout << std::endl;
}

void Printer::printNotFound(std::clock_t duration)
{
    std::cout << "Shape not found, it took: " << duration << " ticks" << std::endl << std::endl;;
}

void Printer::printUnknown(int batchNumber){
    std::cout << "Specification number: " << std::to_string(batchNumber) << " is invalid!" << std::endl << std::endl;
}

void Printer::print(std::string input){
    std::cout << input << std::endl;
}