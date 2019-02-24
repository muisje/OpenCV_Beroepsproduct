#include "../include/drawer.h"
#include <vector>

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::draw(cv::InputOutputArray image, std::vector<DetailedShape> detailedShapes)
{
    if (detailedShapes.size() == 0)
    {
        drawNotFound(image);
    }
    for (auto shape : detailedShapes)
    {
        cv::drawContours(image, std::vector<std::vector<cv::Point> >(1, shape.contour), -1, cv::Scalar(0, 0, 0), 3, 3);
        cv::circle(image, shape.middlepoint, 1, cv::Scalar(0, 0, 0), 3); // center
        drawInfo(image, shape.middlepoint, shape.surface, 000);
    }
}

void Drawer::draw(cv::InputOutputArray image, std::vector<cv::Vec3f> circles)
{
    if (circles.size() == 0)
    {
        drawNotFound(image);
    }
    else
    {
        for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
        {
            cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
            int radius = std::round(circles[current_circle][2]);

            double area = M_PI * pow(radius, 2);
            cv::circle(image, center, 1, cv::Scalar(0, 0, 0), 3);      // center
            cv::circle(image, center, radius, cv::Scalar(0, 0, 0), 3); // contour
            drawInfo(image, center, area, 000, radius + 6);
        }
    }
}

void Drawer::drawNotFound(cv::InputOutputArray image)
{
    std::string textNotFound = "Not Found";
    std::string textTicks = "000 ms";
    std::string text = textNotFound + " " + textTicks;

    cv::Size textSize = cv::getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                        4, 5, 0);
    putText(image, text, cv::Point((image.getMat().cols / 2) - (textSize.width / 2), (image.getMat().rows / 2) - (textSize.height / 2)), CV_FONT_HERSHEY_PLAIN, 4, cv::Scalar(0, 0, 0), 5);
}

void Drawer::drawInfo(cv::InputOutputArray image, cv::Point center, double area, double ticks, int yOffset)
{
    std::string textCenter = "(" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
    std::string textArea = std::to_string(int(round(area))) + " px^2";
    std::string textTicks = std::to_string(int(round(ticks))) + " ms";
    std::string text = textCenter + " " + textArea + " " + textTicks;

    cv::Size textSize = cv::getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                        1, 1, 0);
    putText(image, text, cv::Point(center.x - (textSize.width / 2), center.y - yOffset), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0), 1);
}