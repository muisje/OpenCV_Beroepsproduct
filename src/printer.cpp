#include "../include/printer.h"
#include <vector>

void Printer::print(std::vector<cv::Vec3f> circles)
{
    for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
        {
            cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
            int radius = std::round(circles[current_circle][2]);

            double area = M_PI * pow(radius, 2);
            std::cout << "(" << center.x << ", " << center.y << ")" << area << " px^2 " << "0 ms" <<std::endl;
        }
    std::cout << std::endl;
}
 
void Printer::print(std::vector<DetailedShape> shapes)
{
    for (DetailedShape shape : shapes)
    {
        std::cout << "(" << shape.middlepoint.x << ", " << shape.middlepoint.y << ") " << shape.surface << " px^2 " << "0 ms" <<  std::endl;
    }
    std::cout << std::endl;
}

void Printer::printNotFound()
{
    std::cout << "Not Found" << std::endl << std::endl;   
}