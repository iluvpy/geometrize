#include "Geometrize.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <limits>
#include "Debug.hpp"

Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image.clone();
    m_shapeImage = image.clone();

    int width = image.cols;
    int height = image.rows;

    // clear image (all pixels to black)
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

void Geometrize::sortBestShapes() {
    for (int i = 0; i < m_shapes.size(); i++) {
        m_shapes[i].calculateScore(m_originalImage, m_shapeImage);
    }

    std::sort(m_shapes.begin(), m_shapes.end());
}

void Geometrize::mutateShapes() {
    int size = m_shapes.size();
    // mutate shapes
    for (int i = 0; i < size; i++) {
        Shape mutatedCopy = m_shapes[i];
        mutatedCopy.mutate();
        m_shapes.push_back(mutatedCopy);
        m_shapes[i].mutate();
    }
}


void Geometrize::findBestShapes() {
    //std::cout << "finding best shape\n";
    // bubble sort the shapes //XXX make a better sort
    // calculate the score
    sortBestShapes();
 
    // delete worst shapes
    int halfIndex = (int)(m_shapes.size()/2);
    while (m_shapes.size() > halfIndex) {
        m_shapes.pop_back();
    }
    

}

void Geometrize::update() {
    
    findBestShapes();
    mutateShapes();
    sortBestShapes();
    
    m_shapeImage = m_shapes[0].addShapeToImage(m_shapeImage);
    DEBUG_LOG(m_shapes.size());
    cv::imwrite("shape_img.png", m_shapeImage);
    cv::imwrite("color_diff.png", getColorDiffImage());
    DEBUG_LOG("saved shape img");
}


cv::Mat Geometrize::getColorDiffImage() {
    cv::Mat resultImg;
    cv::subtract(m_shapeImage, m_originalImage, resultImg);
    return resultImg;
}
