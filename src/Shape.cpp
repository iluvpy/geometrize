#include "Shape.hpp"
#include <iostream>

Shape::Shape(int imageWidth, int imageHeight) {
    m_imageW = imageWidth;
    m_imageH = imageHeight;
}

Shape::Shape() {
    m_imageW = 0;
    m_imageH = 0;
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
    m_x = Util::getRandInt(0, m_imageW-m_width/2);
    m_y = Util::getRandInt(0, m_imageH-m_height/2);
    m_color = Util::getRandomColor();
    m_angle = 0;
    std::vector<std::vector<bool>> mat = getMat(m_width+100, m_height+100);
    
    // create circle using the randomly generated values
    int radius = (int)(m_width/2);
    int i = 0;
    int k = 0;
    for(int y=-radius; y<=radius; y++) {
        for(int x=-radius; x<=radius; x++) {
            if(x*x+y*y <= radius*radius) {
                // std::cout << "w: " << m_width << " h: " << m_height << std::endl;
                // std::cout << "i: " << i << " k: " << k << std::endl;
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
    m_x = Util::getRandInt(0, m_imageW-m_width/2);
    m_y = Util::getRandInt(0, m_imageH-m_height/2);
    m_color = Util::getRandomColor();
    m_angle = Util::getRandInt(0, 360);
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
        for (int k = 0; k < height; k++) {
            layer.push_back(false);
        }
        mat.push_back(layer);
    }
    return mat;
}

cv::Mat Shape::addShapeToImage(cv::Mat srcImage) {
    for (int y = m_y; y < m_imageH; y++) {
        for (int x = m_x; x < m_imageW; x++) {
            if (m_shapeMat[y][x]) {
                srcImage.at<cv::Vec3b>(y, x) = cv::Vec3b(m_color.r, m_color.g, m_color.b);
            }
        }
    }
    return srcImage;
}



// will add the current shape to the image, subtract the new image to the old one
// and then sum all the pixel values and returning them, the smaller the value the better
int Shape::getScore(cv::Mat image) {
    cv::Mat imgWithShape = addShapeToImage(image);
    int sum = 0;
    for (int y = 0; y < m_imageH; y++) {
        for (int x = 0; x < m_imageW; x++) {
            cv::Vec3b p1 = image.at<cv::Vec3b>(y, x);
            cv::Vec3b p2 = imgWithShape.at<cv::Vec3b>(y, x);
            sum += p1[0] - p2[0] + p1[1] - p2[1] + p1[2] - p2[2];
        }
    }
    return sum;
}


cv::Mat Shape::getImageWithShape(cv::Mat image) {
    return addShapeToImage(image);
}
