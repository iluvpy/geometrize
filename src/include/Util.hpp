#pragma once
#include <random>
#include "Color.hpp"
#include "Point.hpp"

namespace Util {
    int getRandInt(int min, int max);
    Color getRandomColor();
    Point rotatePoint(const Point& p, const Point& origin, float angle);    
    float toRad(float angle);
}