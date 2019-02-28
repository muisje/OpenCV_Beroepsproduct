#include "../include/drawer.h"
#include <vector>

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::draw(cv::InputOutputArray image, std::vector<DetailedShape> detailedShapes, Specification specification)
{
    if (detailedShapes.size() == 0)
    {
        if (specification.shape == UNKNOWN_SHAPE || specification.colour == UNKNOWN_COLOUR)
        {
            drawText(image, "Unknown input");
        }
        else
        {
            drawText(image, "Not Found");
        }
    }
    for (auto shape : detailedShapes)
    {
        cv::RotatedRect rect = cv::minAreaRect(shape.contour);
        cv::Point2f vertices[4];
        rect.points(vertices);
        for (int i = 0; i < 4; i++)
            line(image, vertices[i], vertices[(i + 1) % 4], cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE));
        // cv::drawContours(image, std::vector<std::vector<cv::Point> >(1, contour), -1, cv::Scalar(255, 255, 0), 1, 1);
        cv::circle(image, shape.middlepoint, 1, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 3); // center
        drawInfo(image, shape.middlepoint, shape.surface, 000);
    }
}

void Drawer::draw(cv::InputOutputArray image, std::vector<cv::Vec3f> circles, Specification specification)
{
    if (circles.size() == 0)
    {
        if (specification.shape == UNKNOWN_SHAPE || specification.colour == UNKNOWN_COLOUR)
        {
            drawText(image, "Unknown input");
        }
        else
        {
            drawText(image, "Not Found");
        }
    }
    else
    {
        for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
        {
            cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
            int radius = std::round(circles[current_circle][2]);

            double area = M_PI * pow(radius, 2);
            cv::circle(image, center, 1, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 3);      // center
            cv::circle(image, center, radius, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 3); // contour
            drawInfo(image, center, area, 000, radius + 6);
        }
    }
}

void Drawer::drawText(cv::InputOutputArray image, std::string inputText)
{
    std::string textTicks = "000 ms";
    std::string text = inputText + " " + textTicks;

    cv::Size textSize = cv::getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                        4, 5, 0);
    putText(image, text, cv::Point((image.getMat().cols / 2) - (textSize.width / 2), (image.getMat().rows / 2) - (textSize.height / 2)), CV_FONT_HERSHEY_PLAIN, 4, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 5);
}

void Drawer::drawInfo(cv::InputOutputArray image, cv::Point center, double area, double ticks, int yOffset)
{
    std::string textCenter = "(" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
    std::string textArea = std::to_string(int(round(area))) + " px^2";
    std::string textTicks = std::to_string(int(round(ticks))) + " ms";
    std::string text = textCenter + " " + textArea + " " + textTicks;

    cv::Size textSize = cv::getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                        1, 1, 0);
    putText(image, text, cv::Point(center.x - (textSize.width / 2), center.y - yOffset), CV_FONT_NORMAL, 0.5, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 1);
}