#include "Util.hpp"

int Util::getRandInt(int min, int max) {
    return min + rand() % max;
}

Color Util::getRandomColor() {
    return Color{(uint8)getRandInt(0, 255), (uint8)getRandInt(0, 255), (uint8)getRandInt(0, 255)};
}

float Util::toRad(float angle) {
	return M_PI / 180 * angle; 
}

Point Util::rotatePoint(const Point& p, const Point& origin, float angle) {
    float _sin = sin(angle);
	float _cos = cos(angle);

	float ox = origin.x;
	float oy = origin.y;

	float x = p.x - ox;
	float y = p.y - oy;

	float new_x = x * _cos - y * _sin;
	float new_y = y * _cos + x * _sin;

	new_x += ox;
	new_y += oy;

    return Point{(int)new_x, (int)new_y};
}    
