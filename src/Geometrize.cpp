#include "Geometrize.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <limits>

Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image.clone();
    m_shapeImage = image.clone();
    int width = image.cols;
    int height = image.rows;
    std::cout << "generating " << MAX_SHAPES << " random shapes\n";
    for (int i = 0; i < MAX_SHAPES; i++) {
        Shape shape(width, height);
        shape.generateRandomShape();
        m_shapes.push_back(shape);
    }

    // clear image (all pixels to white)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_shapeImage.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255); 
        }
    }

    std::cout << "finished generating\n";
}



cv::Mat Geometrize::getShapeImage() {
    return m_shapeImage;
}


void Geometrize::update() {
    double bestScore = std::numeric_limits<double>::max();
    Shape bestShape;
    std::cout << "finding best shape\n";
    for (auto& shape : m_shapes) {
        double score = shape.getScore(m_originalImage, m_shapeImage);
        if (score < bestScore) {
            //std::cout << "new best shape found\n";
            bestScore = score;
            bestShape = shape;
        }
    }
    std::cout << "found best shape\n";
    cv::Mat img = bestShape.getImageWithShape(m_shapeImage);
    m_shapeImage = img;
    cv::imwrite("save.png", m_shapeImage);
    
}
