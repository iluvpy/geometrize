#include "Geometrize.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <limits>

Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image.clone();
    m_shapeImage = image.clone();

    int width = image.cols;
    int height = image.rows;

    // clear image (all pixels to white)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_shapeImage.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255); 
        }
    }
    std::cout << "generating " << MAX_SHAPES << " random shapes\n";
    generateShapes();
    std::cout << "finished generating\n";
}

void Geometrize::generateShapes() {
    int width = m_originalImage.cols;
    int height = m_originalImage.rows;
    for (int i = 0; i < MAX_SHAPES; i++) {
        Shape shape(width, height);
        shape.generateRandomShape();
        m_shapes.push_back(shape);
    }

}


cv::Mat Geometrize::getShapeImage() {
    return m_shapeImage;
}

void Geometrize::findBestShapes(Shape *bestShape) {
    //std::cout << "finding best shape\n";
    // bubble sort the shapes //XXX make a better sort
    // calculate the scores
    for (int i = 0; i < m_shapes.size(); i++) {
        m_shapes[i].calculateScore(m_originalImage, m_shapeImage);
    }

    std::sort(m_shapes.begin(), m_shapes.end());
 
    //set best shape
    *bestShape = m_shapes[0]; 

    // delete worst shapes
    int halfIndex = (int)(m_shapes.size()/2);
    while (m_shapes.size() > halfIndex) {
        m_shapes.pop_back();
    }

    int size = m_shapes.size();
    std::cout << size;
    // mutate shapes
    for (int i = 0; i < size; i++) {
        Shape mutatedCopy = m_shapes[i];
        mutatedCopy.mutate();
        m_shapes.push_back(mutatedCopy);
    }
}

void Geometrize::update() {
    Shape bestShape;
    for (int i = 0; i < 1; i++) {
        findBestShapes(&bestShape);
    }
    cv::Mat img = bestShape.getImageWithShape(m_shapeImage);
    m_shapeImage = img;
    cv::imwrite("shape_img.png", m_shapeImage);
}
