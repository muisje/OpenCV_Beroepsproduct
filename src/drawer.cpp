#include "../include/drawer.h"
#include <vector>

Drawer::Drawer()
{
}

Drawer::~Drawer()
{
}

void Drawer::draw(cv::InputOutputArray image, Specification specification)
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

void Drawer::draw(cv::InputOutputArray image, std::vector<DetailedShape> detailedShapes, Specification specification, std::clock_t duration)
{
    if (detailedShapes.size() == 0)
    {
        draw(image, specification);
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
        drawTime(image, duration);

}

void Drawer::draw(cv::InputOutputArray image, std::vector<cv::Vec3f> circles, Specification specification, std::clock_t duration)
{
    if (circles.size() == 0)
    {
        draw(image, specification);
    }
    else
    {
        for (size_t current_circle = 0; current_circle < circles.size(); ++current_circle)
        {
            cv::Point center(static_cast<int>(std::round(circles[current_circle][0])), static_cast<int>(std::round(circles[current_circle][1])));
            int radius = static_cast<int>(std::round(circles[current_circle][2]));

            double area = M_PI * pow(radius, 2);
            cv::circle(image, center, 1, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 3);      // center
            cv::circle(image, center, radius, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 3); // contour
            drawInfo(image, center, area, radius + 6);
        }
    }
    drawTime(image, duration);
}

void Drawer::drawText(cv::InputOutputArray image, std::string inputText)
{
    cv::Size textSize = cv::getTextSize(inputText, CV_FONT_HERSHEY_PLAIN,
                                        4, 5, 0);
    putText(image, inputText, cv::Point((image.getMat().cols / 2) - (textSize.width / 2), (image.getMat().rows / 2) - (textSize.height / 2)), CV_FONT_HERSHEY_PLAIN, 4, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 5);
}

void Drawer::drawInfo(cv::InputOutputArray image, cv::Point center, double area, int yOffset)
{
     std::string textCenter = "(" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
    std::string textArea = std::to_string(int(round(area))) + " px^2";
    std::string text = textCenter + " " + textArea;

    cv::Size textSize = cv::getTextSize(text, CV_FONT_HERSHEY_PLAIN,
                                        1, 1, 0);
    putText(image, text, cv::Point(center.x - (textSize.width / 2), center.y - yOffset), CV_FONT_NORMAL, 0.5, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 1);
}

void Drawer::drawTime(cv::InputOutputArray image, std::clock_t duration)
{
    std::string text = std::to_string(duration) + "clock ticks";
    putText(image, text, cv::Point(10, 30), CV_FONT_NORMAL, 1.0, cv::Scalar(TEXT_RED, TEXT_GREEN, TEXT_BLUE), 1);
}