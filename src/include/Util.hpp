#pragma once
#include <random>
#include <opencv2/core.hpp>
#include "Color.hpp"
#include "Point.hpp"
#include "Rect.hpp"

namespace Util {
    int getRandInt(int min, int max);
    Color getRandomColor();
    Point rotatePoint(const Point& p, const Point& origin, float angle);    
    float toRad(float angle);
    double calculatePixelDifferenceAt(cv::Mat image, cv::Mat image2, Rect rectangle);

}