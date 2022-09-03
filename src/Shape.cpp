#include "Shape.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

Shape::Shape(int imageWidth, int imageHeight) {
    m_imageW = imageWidth;
    m_imageH = imageHeight;
    m_score = DEFAULT_SCORE;
}

Shape::Shape() {
    m_imageW = 0;
    m_imageH = 0;
    m_score = DEFAULT_SCORE;
}

std::vector<std::vector<bool>> Shape::getShapeMat() const {
    return m_shapeMat;
}

Color Shape::getColor() const {
    return m_color;
}

Point Shape::getPosition() const {
    return Point{m_x, m_y};
}

void Shape::generateRandomShape() {
    //m_shape = getRandomShape();
    // switch (m_shape)
    // {
    //     case Circle:
    //         m_shapeMat = createRandomCircle();
    //         break;
    //     case Triangle:
    //         m_shapeMat = createRandomTriangle();
    //         break;
    //     case Cube:
    //         m_shapeMat = createRandomCube);
    //         break; 
    //     case Rectangle:
    //         m_shapeMat = createRandomRectangle();
    //         break;
    // }
    // for testing purpose im only gonna use circles for now
    m_shapeType = Shapes::Circle;
    createRandomCircle();
}

Shapes Shape::getRandomShape() {
    return (Shapes)Util::getRandInt(0, Shapes::LAST-1);
}

void Shape::createRandomCircle() {
    m_width = Util::getRandInt(MIN_CIRCLE_DIAMETER, MAX_CIRCLE_DIAMETER);
    m_height = m_width;

    // generating random values for x y in a range where the circle is visible
    m_x = Util::getRandInt(-m_width+1, m_imageW-1);
    m_y = Util::getRandInt(-m_height+1, m_imageH-1);
    m_color = Util::getRandomColor();
    m_angle = 0;
    createCircle();
}

void Shape::createCircle() {
    std::vector<std::vector<bool>> mat = getMat(m_width, m_height);
    
    // create circle using the randomly generated values
    int radius = (int)(m_width/2)-1;
    int i = 0;
    int k = 0;
    for(int y=-radius; y <= radius; y++) {
        for(int x=-radius; x <= radius; x++) {
            if(x*x+y*y <= radius*radius) {
                mat[i][k] = true;
            }
            k++;
        }
        i++;
        k = 0;
    }
    m_shapeMat = mat;
}

void Shape::createRandomTriangle() {
    m_width = Util::getRandInt(TRIANGLE_BASE_MIN, TRIANGLE_BASE_MAX);
    m_height = Util::getRandInt(TRIANGLE_HEIGHT_MIN, TRIANGLE_HEIGHT_MAX);
    m_x = Util::getRandInt(-m_width+1, m_imageW+m_width-1);
    m_y = Util::getRandInt(-m_height+1, m_imageH-1);
    m_color = Util::getRandomColor();
    m_angle = Util::getRandInt(0, 360);
    createTriangle();
}

void Shape::createTriangle() {
    std::vector<std::vector<bool>> mat;

    // create triangle using the randomly generated values
    double actualRatio = m_width/m_height;
    int width = 0;
    int height = 0;
    while (width < m_width) {
        
        std::vector<bool> layer;
        double ratio = width/height; // if adding another pixel in width will bring the triangle closer to the actual w/h ratio 
        while ((actualRatio-ratio) > (actualRatio-(width+1/height))) {
            layer.push_back(true);
            width++;
            ratio = width/height;
        }
        mat.push_back(layer);
        height++;
    }

    // rotate
    //std::vector<std::vector<bool>> rotatedMat;
}

void Shape::createRandomCube() {

}

void Shape::createRandomRectangle() {

}

std::vector<std::vector<bool>> Shape::getMat(int width, int height) {
    std::vector<std::vector<bool>> mat;
    for (int i = 0; i < height; i++) {
        std::vector<bool> layer;
        for (int j = 0; j < height; j++) {
            layer.push_back(false);
        }
        mat.push_back(layer);
    }
    return mat;
}

cv::Mat Shape::addShapeToImage(cv::Mat srcImage) const{

    int y = m_y-1;
    int x = m_x-1;
    for (const auto& layer : m_shapeMat) {
        for (const auto& pixel : layer) {
            if (pixel) {
                if (x < m_imageW && y < m_imageH && y >= 0 && x >= 0) {
                    // calculate average 
                    int r = (srcImage.at<cv::Vec3b>(y, x)[2] + m_color.r) / 2; 
                    int g = (srcImage.at<cv::Vec3b>(y, x)[1] + m_color.g) / 2; 
                    int b = (srcImage.at<cv::Vec3b>(y, x)[0] + m_color.b) / 2; 
                    srcImage.at<cv::Vec3b>(y, x)[2] = r;
                    srcImage.at<cv::Vec3b>(y, x)[1] = g;
                    srcImage.at<cv::Vec3b>(y, x)[0] = b;
                }
            }
            x++;
        }
        y++;
        x = m_x;
    }
    return srcImage;
}


// calculates a new score and sets the score member 
void Shape::calculateScore(cv::Mat originalImage, cv::Mat shapeImage) {
    cv::Mat imgWithShape = addShapeToImage(shapeImage.clone());
    double pixelDiffNoImage = Util::calculatePixelDifferenceAt(originalImage, shapeImage, Rect{m_x, m_y, m_width, m_height});
    double pixelDiffWithShape = Util::calculatePixelDifferenceAt(originalImage, imgWithShape, Rect{m_x, m_y, m_width, m_height});
    // the smaller the pixel difference with the shape is the bigger the bigger the score
    m_score = pixelDiffNoImage - pixelDiffWithShape;
}



// returns the score member
double Shape::getScore() const {
    return m_score;
}   


int Shape::getWidth() {
    return m_width;
}

// 50% chance of mutation
void Shape::mutate() {
    if (Util::getRandInt(0, 1)) {
        return;
    }
    switch (m_shapeType)
    {
        case Circle:
            return mutateCircle();
            break;
        
        case Triangle:
            return mutateTriangle();
            break;

        case Cube:
            return mutateCube();
            break;

        case Rectangle:
            return mutateRectangle();
            break;
        
        default:
            break;
    }
}

const Shape& Shape::copy() const {
    return *this;
}

// returns a valid mutation value for with or height
int Shape::getWHMutation(int min, int max) {
    int randInt;
    do {
        randInt = Util::getRandInt(min, max);
    } while ((m_width+randInt < MIN_SHAPE_WIDTH) && randInt);
    return randInt;
}

int Shape::getXMutation(int min, int max) {
    int randInt;
    int new_x;
    // while the value for x is not valid, generate a new one
    do {
        randInt = Util::getRandInt(min, max);
        new_x = m_x + randInt;
    } while ((new_x+m_width < MIN_VISIBILITY || new_x-m_width > m_imageW-MIN_VISIBILITY) && randInt);
    return randInt;
}

int Shape::getYMutation(int min, int max) {
    int randInt;
    int new_y;
    // while the value for y is not valid, generate a new one
    do {
        randInt = Util::getRandInt(min, max);
        new_y = m_y + randInt;
    } while ((new_y+m_height < MIN_VISIBILITY || new_y-m_height > m_imageH-MIN_VISIBILITY) && randInt);
    return randInt;
}

int Shape::getColorMut(int min, int max, short int initialColor) {
    int randInt;
    do {
        randInt = Util::getRandInt(min, max);
    } while ((initialColor+randInt < 0 || initialColor+randInt > 255) && randInt);
    return randInt;
}


void Shape::mutateCircle() {
    m_width += getWHMutation(-CIRCLE_MUTATION_RANGE, CIRCLE_MUTATION_RANGE);
    m_height = m_width;
    // the width can be changed by CIRCLE_MUTATION_RANGE an if it does then it would be 
    // impossible to generate visible xy 
    m_x += getXMutation(-CIRCLE_MUTATION_RANGE-MIN_VISIBILITY, CIRCLE_MUTATION_RANGE+MIN_VISIBILITY);
    m_y += getYMutation(-CIRCLE_MUTATION_RANGE-MIN_VISIBILITY, CIRCLE_MUTATION_RANGE+MIN_VISIBILITY);
    m_color.r += getColorMut(-CIRCLE_MUTATION_RANGE, CIRCLE_MUTATION_RANGE, m_color.r);
    m_color.g += getColorMut(-CIRCLE_MUTATION_RANGE, CIRCLE_MUTATION_RANGE, m_color.g);
    m_color.b += getColorMut(-CIRCLE_MUTATION_RANGE, CIRCLE_MUTATION_RANGE, m_color.b);
    m_angle = 0;
    createCircle();
}

void Shape::mutateTriangle() {

}

void Shape::mutateCube() {

}

void Shape::mutateRectangle() {

}
