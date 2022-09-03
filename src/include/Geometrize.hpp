#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <limits>
#include <iostream>
#include "Shape.hpp"

#define MAX_SHAPES 100
#define MIN_SCORE 100

class Geometrize {
public:
    Geometrize(const cv::Mat& originalImage, const cv::Mat& shapeImage);
    void update();
    void generateShapes();
    void sortBestShapes();
    void mutateShapes();
    void deleteWorst();
    int getGeneration() const;
    const Shape& getCurrentBestShape() const;
    cv::Mat getColorDiffImage();
    cv::Mat getShapeImage();
private:
    Shape m_bestShape;
    cv::Mat m_originalImage;
    cv::Mat m_shapeImage;
    std::vector<Shape> m_shapes;
    int m_generation;
};