#include "Geometrize.hpp"
#include "Debug.hpp"

Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image.clone();
    m_shapeImage = image.clone();
    m_generation = 0;
    
    int width = image.cols;
    int height = image.rows;

    // calculate average pixel value of original image and set the 
    // shape image background to that average
    double b_sum = 0.0;
    double g_sum = 0.0;
    double r_sum = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            b_sum += m_originalImage.at<cv::Vec3b>(i, j)[0]; 
            g_sum += m_originalImage.at<cv::Vec3b>(i, j)[1]; 
            r_sum += m_originalImage.at<cv::Vec3b>(i, j)[2]; 
        }
    }

    int pixels = width*height;
    b_sum /= pixels;
    g_sum /= pixels;
    r_sum /= pixels;

    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_shapeImage.at<cv::Vec3b>(i, j)[0] = b_sum; 
            m_shapeImage.at<cv::Vec3b>(i, j)[1] = g_sum; 
            m_shapeImage.at<cv::Vec3b>(i, j)[2] = r_sum; 
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

    // calculate the scores
    for (int i = 0; i < m_shapes.size(); i++) {
        m_shapes[i].calculateScore(m_originalImage, m_shapeImage);
    }

    // sort biggest to smallest
    std::sort(m_shapes.begin(), m_shapes.end(), std::greater<>());
}

void Geometrize::mutateShapes() {
    int size = m_shapes.size();
    // mutate shapes
    for (int i = 0; i < size; i++) {
        Shape mutatedCopy = m_shapes[i];
        mutatedCopy.mutate();
        m_shapes.push_back(mutatedCopy);
    }
}


void Geometrize::deleteWorst() {
    // delete worst shapes (lower half)
    int halfIndex = (int)(m_shapes.size()/2);
    while (m_shapes.size() > halfIndex) {
        m_shapes.pop_back();
    }
}



void Geometrize::update() {
    int score;
    int tries = 0;
    do {
        sortBestShapes();
        score = m_shapes[0].getScore();
        if (score > 0) {
            m_shapes[0].addShapeToImage(m_shapeImage);
            std::cout << "score: " << score << std::endl;
            std::cout << "generation: " << m_generation << std::endl;
        } 
        deleteWorst();
        mutateShapes();
        tries++;
        std::cout << "finished generation!\n";
    } while (score < 1);
    std::cout << "tries: " << tries << std::endl;
    
    cv::imwrite("shape_img.png", m_shapeImage);
    cv::imwrite("color_diff.png", getColorDiffImage());
    m_generation++;
}


cv::Mat Geometrize::getColorDiffImage() {
    cv::Mat resultImg;
    cv::subtract(m_shapeImage, m_originalImage, resultImg);
    return resultImg;
}
