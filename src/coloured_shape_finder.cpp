#include "../include/coloured_shape_finder.h"
#include "../include/shape_filter.h"
#include "../include/colour_filter.h"
#include <opencv2/opencv.hpp>

ColouredShapeFinder::ColouredShapeFinder()
{
}

ColouredShapeFinder::~ColouredShapeFinder()
{
}

std::vector<DetailedShape> ColouredShapeFinder::find(cv::Mat image, Specification specification)
{
    std::vector<DetailedShape> detailedShapes;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::Mat hsvImage;
    cvtColor(image, hsvImage, CV_BGR2HSV);
    cv::Mat preservedImage = hsvImage.clone();
    cv::Mat preservedImage2 = hsvImage.clone();

    cv::bilateralFilter(hsvImage, preservedImage2, 5, 85, 85);

    preservedImage2 = ColourFilter::preserveColour(preservedImage2, specification.colour);
    cv::bilateralFilter(preservedImage2, preservedImage, 5, 85, 85);

    /*
    cv::Mat canny;
    cv::Mat finalImage;

    cv::Canny(image, canny, 50, 200);
    cv::GaussianBlur(canny, canny, cv::Size(3, 3), 3, 3);                   // perfect for wood
    cv::GaussianBlur(preservedImage, preservedImage, cv::Size(3, 3), 3, 3); // perfect for wood

    cv::bitwise_and(canny, preservedImage, finalImage);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * 1 + 1, 2 * 1 + 1), cv::Point(-1, -1));
    cv::morphologyEx(finalImage, finalImage, cv::MORPH_DILATE, element, cv::Point(-1, -1), 1);
    imshow("final", finalImage);
*/
    cv::findContours(preservedImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    preservedImage = ShapeFilter::removeSmallContours(preservedImage, contours);
    imshow("sdf", preservedImage);

    for (size_t i = 0; i < contours.size(); ++i)
    {
        std::vector<cv::Point> approx;
        approxPolyDP(contours[i], approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.05, true);
        switch (specification.shape)
        {
        case RECTANGLE:
        case SQUARE:
        case QUADRANGLE:
            if (approx.size() == 4)
            {
                if (ShapeFilter::isShape(approx, specification.shape))
                {
                    detailedShapes.push_back(DetailedShape(contours[i], specification));
                }
            }
            break;
        case CIRCLE:
            std::cout << "Use findCircles instead" << std::endl;
            break;
        case TRIANGLE:
            if (approx.size() == 3 && !ShapeFilter::isHalfCircle(contours[i])) // When an halfCircle is to small approxPolyDP in rare occasions only recognizes 3 "corners"
            {
                detailedShapes.push_back(DetailedShape(contours[i], specification));
            }
            break;
        case HALF_CIRCLE:
            if (ShapeFilter::isHalfCircle(contours[i]))
            {
                detailedShapes.push_back(DetailedShape(contours[i], specification));
            }
            break;
        }
    }
    return detailedShapes;
}

std::vector<cv::Vec3f> ColouredShapeFinder::findCircles(cv::Mat image, enum ::Colour colour)
{
    cv::Mat dst_x = image.clone();
    cv::Mat dst_y = image.clone();
    cv::Mat dst_combined = image.clone();

    cv::Scharr(image, dst_x, -1, 1, 0, 1.0, 300);
    cv::Scharr(image, dst_y, -1, 0, 1, 1.0, 300);

    cv::addWeighted(dst_x, 0.5, dst_y, 0.5, 0, dst_combined);

    cv::Mat hsv;
    cvtColor(image, hsv, CV_BGR2HSV);
    cv::Mat foundCircles = ColourFilter::preserveColour(hsv, colour);
    cvtColor(dst_combined, dst_combined, cv::COLOR_BGR2GRAY);
    subtract(foundCircles, dst_combined, foundCircles);

    cv::GaussianBlur(foundCircles, foundCircles, cv::Size(3, 3), 3, 3); // perfect for wood
    //TODO find blur for surface of blocks (so its flat, smooth and solid)
    // cv::GaussianBlur(foundCircles, foundCircles, cv::Size(5, 5), 3, 3); // perfect for yellow

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(foundCircles, circles, CV_HOUGH_GRADIENT, 1, foundCircles.rows / 8, 100, 30, 15, 100);
    return circles;
}