#include "Geometrize.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image;
    m_image = image;
    std::cout << "generating " << MAX_SHAPES << " random shapes\n";
    for (int i = 0; i < MAX_SHAPES; i++) {
        Shape shape;
        shape.generateRandomShape();
        m_shapes.push_back(shape);
    }
    std::cout << "finished generating\n";
}

Shape Geometrize::getBestShape() {
    return m_bestShape;
}


void Geometrize::update() {
    int bestScore = INT32_MAX;
    Shape bestShape;
    std::cout << "finding best shape\n";
    for (auto& shape : m_shapes) {
        int score = shape.getScore(m_originalImage);
        if (score < bestScore) {
            bestScore = score;
            bestShape = shape;
        }
    }
    std::cout << "found best shape\n";
    m_bestShape = bestShape;
    cv::Mat img = m_bestShape.getImageWithShape(m_image);
    cv::imwrite("./save.jpg", img);
    exit(-1);
}
