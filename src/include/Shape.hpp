#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include <limits>
#include "Pixel.hpp"
#include "Color.hpp"

#define MAX_CIRCLE_DIAMETER 800
#define MIN_CIRCLE_DIAMETER 5
#define CIRCLE_MUTATION_RANGE 20

#define TRIANGLE_BASE_MAX 800
#define TRIANGLE_BASE_MIN 5
#define TRIANGLE_HEIGHT_MAX 800
#define TRIANGLE_HEIGHT_MIN 5
#define TRIANGLE_PADDING 200 

#define DEFAULT_SCORE std::numeric_limits<double>::max()


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
    Shape();
    void generateRandomShape();
    void mutate();
    void calculateScore(cv::Mat originalImage, cv::Mat shapeImage);
    double getScore() const;
    const Shape& copy() const;
    std::vector<std::vector<bool>> getShapeMat() const;
    Color getColor() const;
    Point getPosition() const;
    cv::Mat getImageWithShape(cv::Mat image);
    cv::Mat addShapeToImage(cv::Mat srcImage) const;

    bool operator>(const Shape& other) {
        return getScore() > other.getScore();
    }

    bool operator<(const Shape& other) {
        return getScore() < other.getScore();
    }

    bool operator==(const Shape& other) {
        return getScore() == other.getScore();
    }

private:
    int m_x; // position of the shape in the image
    int m_y; // position of the shape in the image
    int m_width;
    int m_height;
    int m_imageW;
    int m_imageH;
    int m_angle;
    double m_score;
    Shapes m_shapeType;
    Color m_color;
    std::vector<std::vector<bool>> m_shapeMat;

    Shapes getRandomShape();
    void createCircle();
    void createRandomCircle();
    void createTriangle();
    void createRandomTriangle();
    void createRandomCube();
    void createRandomRectangle();
    void mutateCircle();
    void mutateTriangle();
    void mutateCube();
    void mutateRectangle();
    std::vector<std::vector<bool>> getMat(int width, int height);
};