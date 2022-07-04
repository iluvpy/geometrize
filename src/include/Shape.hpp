#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include "Pixel.hpp"
#include "Color.hpp"

#define MAX_CIRCLE_DIAMETER 800
#define MIN_CIRCLE_DIAMETER 5

#define TRIANGLE_BASE_MAX 800
#define TRIANGLE_BASE_MIN 5
#define TRIANGLE_HEIGHT_MAX 800
#define TRIANGLE_HEIGHT_MIN 5
#define TRIANGLE_PADDING 200 


// for now im gonna only use these shapes
enum Shapes : unsigned char {
    Circle,
    Triangle,
    Cube,
    Rectangle,
    LAST
};

class Shape {
public:
    Shape(int imageWidth, int imageHeight);
    void generateRandomShape();
    int getScore(cv::Mat image);
private:
    int m_x; // position of the shape in the image
    int m_y; // position of the shape in the image
    int m_width;
    int m_height;
    int m_imageW;
    int m_imageH;
    int m_angle;
    Shapes m_shape;
    Color m_color;
    std::vector<std::vector<bool>> m_shapeMat;

    Shapes getRandomShape();
    void createRandomCircle();
    void createRandomTriangle();
    void createRandomCube();
    void createRandomRectangle();
    cv::Mat addShapeToImage(cv::Mat srcImage);
    std::vector<std::vector<bool>> getMat(int width, int height);
};