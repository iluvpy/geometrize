#pragma once
#include <vector>
#include "Pixel.hpp"
#include "Color.hpp"

#define MAX_CIRCLE_DIAMETER 800
#define MIN_CIRCLE_DIAMETER 5

#define TRIANGLE_BASE_MAX 800
#define TRIANGLE_BASE_MIN 5
#define TRIANGLE_HEIGHT_MAX 800
#define TRIANGLE_HEIGHT_MIN 5

// how many columns/rows are gonna be added to the shape mat as extra
#define PADDING 1 
// for now im gonna only use these shapes
enum Shapes : unsigned char {
    Circle,
    Triangle,
    Cube,
    Rectangle
}

class Shape {
public:
    Shape(int imageWidth, int imageHeight);
    void generateRandomShape();
private:
    int m_x; // position of the shape in the image
    int m_y; // position of the shape in the image
    int m_width;
    int m_height;
    int m_imageW;
    int m_imageH;
    int m_angle;
    Color m_color;
    std::vector<std::vector<Pixel>> m_shapeMat;

    Shapes getRandomShape();
    void createRandomCircle();
    void createRandomTriangle();
    void createRandomCube();
    void createRandomRectangle();

}