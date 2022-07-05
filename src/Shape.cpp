#include "Shape.hpp"
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
        for (int j = 0; j < height; j++) {
            layer.push_back(false);
        }
        mat.push_back(layer);
    }
    return mat;
}

cv::Mat Shape::addShapeToImage(cv::Mat srcImage) {
    // for (int y = m_y; y < m_imageH; y++) {
    //     for (int x = m_x; x < m_imageW; x++) {
    //         if (m_shapeMat[y][x]) {
    //             int r = srcImage.at<cv::Vec3b>(y, x)[0] + m_color.r;
    //             int g = srcImage.at<cv::Vec3b>(y, x)[1] + m_color.g;
    //             int b = srcImage.at<cv::Vec3b>(y, x)[2] + m_color.b;
               
    //             srcImage.at<cv::Vec3b>(y, x)[0] = r <= 255 ? r : 255;
    //             srcImage.at<cv::Vec3b>(y, x)[1] = g <= 255 ? g : 255;
    //             srcImage.at<cv::Vec3b>(y, x)[2] = b <= 255 ? b : 255;
    //         }
    //     }
    // }

    int y = m_x;
    int x = m_y;
    for (const auto& layer : m_shapeMat) {
        for (const auto& pixel : layer) {
            if (pixel) {
                if (x < m_imageW && y < m_imageH) {
                    int r = srcImage.at<cv::Vec3b>(y, x)[0] + m_color.r;
                    int g = srcImage.at<cv::Vec3b>(y, x)[1] + m_color.g;
                    int b = srcImage.at<cv::Vec3b>(y, x)[2] + m_color.b;

                    srcImage.at<cv::Vec3b>(y, x)[0] = r <= 255 ? r : 255-r;
                    srcImage.at<cv::Vec3b>(y, x)[1] = g <= 255 ? g : 255-g;
                    srcImage.at<cv::Vec3b>(y, x)[2] = b <= 255 ? b : 255-b;
                }
            }
            x++;
        }
        y++;
        x = m_x;
    }
    return srcImage;
}



// will add the current shape to the image, subtract the new image to the old one
// and then sum all the pixel values and returning them, the smaller the value the better
double Shape::getScore(cv::Mat originalImage, cv::Mat shapeImage) {
    cv::Mat imgWithShape = addShapeToImage(shapeImage.clone());
    cv::Mat resultingImage;
    cv::subtract(imgWithShape, originalImage, resultingImage);

    double sum = cv::sum(resultingImage)[0];
    //std::cout << "score: " << sum << std::endl;
    return sum;
}


cv::Mat Shape::getImageWithShape(cv::Mat image) {
    return addShapeToImage(image.clone());
}
