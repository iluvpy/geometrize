#include "Geometrize.hpp"
#include "Debug.hpp"

Geometrize::Geometrize(const cv::Mat& originalImage, const cv::Mat& shapeImage) {
    m_originalImage = originalImage;
    m_shapeImage = shapeImage;
    m_generation = 0;
    
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


// cv::Mat Geometrize::getShapeImage() {
//     return m_shapeImage;
// }

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
    DEBUG_LOG("updating!");
    int score;
    sortBestShapes();
    score = m_shapes[0].getScore();
    m_bestShape = m_shapes[0];
    //m_shapes[0].addShapeToImage(m_shapeImage);
    std::cout << "score: " << score << std::endl;
    std::cout << "generation: " << m_generation << std::endl;

    deleteWorst();
    mutateShapes();
    

    std::cout << "finished generation!\n";
    
    //cv::imwrite("shape_img.png", m_shapeImage);
    m_generation++;
}


cv::Mat Geometrize::getColorDiffImage() {
    cv::Mat resultImg;
    cv::subtract(m_shapeImage, m_originalImage, resultImg);
    return resultImg;
}

int Geometrize::getGeneration() const {
    return m_generation;
}


const Shape& Geometrize::getCurrentBestShape() const {
    return m_bestShape;
}
