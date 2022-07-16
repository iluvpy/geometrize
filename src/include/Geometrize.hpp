#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <limits>
#include <iostream>
#include "Shape.hpp"

#define MAX_SHAPES 100

class Geometrize {
public:
    Geometrize(const cv::Mat& image);
    void update();
    void generateShapes();
    void sortBestShapes();
    void mutateShapes();
    void deleteWorst();
    cv::Mat getColorDiffImage();
    cv::Mat getShapeImage();
private:
    cv::Mat m_originalImage;
    cv::Mat m_shapeImage;
    std::vector<Shape> m_shapes;
};