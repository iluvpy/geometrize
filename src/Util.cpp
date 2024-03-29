#include "Util.hpp"

int Util::getRandInt(int min, int max) {
    int mod_ = (max+1 - min);
    if (mod_ == 0) {
        return 0;
    }
    return min + rand() % mod_;
}

Color Util::getRandomColor() {
	unsigned char r = getRandInt(0, 255);
	unsigned char g = getRandInt(0, 255);
	unsigned char b = getRandInt(0, 255);
    return Color{r, g, b};
}

float Util::toRad(float angle) {
	return M_PI / 180 * angle; 
}

// returns how different an image is from another inside rectangle (all pixels in the rectangle are checked);
// the lower the return value the less difference they have
double Util::calculatePixelDifferenceAt(cv::Mat image, cv::Mat image2, Rect rectangle) {
    int width = image.cols;
    int height = image.rows;
    double score = 0.0;
    for (int i = rectangle.y; i < height && i < rectangle.y+rectangle.height; i++) {
        if (i < 0) continue;
        for (int j = rectangle.x; j < width && j < rectangle.x+rectangle.width; j++) {
            if (j < 0) continue;
            score += std::abs(image.at<cv::Vec3b>(i, j)[0] - image2.at<cv::Vec3b>(i, j)[0]);
            score += std::abs(image.at<cv::Vec3b>(i, j)[1] - image2.at<cv::Vec3b>(i, j)[1]);
            score += std::abs(image.at<cv::Vec3b>(i, j)[2] - image2.at<cv::Vec3b>(i, j)[2]);
        }
    }
    return score;
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
