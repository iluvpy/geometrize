#include "Shape.hpp"


Shape::Shape(int imageWidth, int imageHeight) {

}

void Shape::generateRandomShape() {
    Shapes shape = getRandomShape();
    switch (shape)
    {
        case Circle:
            m_shapeMat = createRandomCircle();
            break;
        case Triangle:
            m_shapeMat = createRandomTriangle();
            break;
        case Cube:
            m_shapeMat = createRandomCube);
            break; 
        case Rectangle:
            m_shapeMat = createRandomRectangle();
            break;
    }
}

Shapes Shape::getRandomShape() {

}

void Shape::createRandomCircle() {
    m_width = Util::getRandInt(MIN_CIRCLE_DIAMETER, MAX_CIRCLE_DIAMETER);
    m_height = m_width;
    m_x = Util::getRandInt(0, m_imageW-m_width/2);
    m_y = Util::getRandInt(0, m_imageH-m_height/2);
    m_color = Util::getRandomColor();
    std::vector<std::vector<Pixel>> mat;
    for (int i = 0; i < m_height; i++) {
        std::vector<Pixel> layer;
        for (int k = 0; k < m_width; k++) {
            Pixel pixel;
            pixel.setValid(false);
            layer.push_back(pixel);
        }
        mat.push_back(layer);
    }
    int radius = m_width/2-PADDING;
    for(int y=-radius; y<=radius; y++) {
        for(int x=-radius; x<=radius; x++) {
            if(x*x+y*y <= radius*radius) {
                mat[y][x].setValid(true);
                mat[y][x].setColor(m_color.r, m_color.g, m_color.g);
            }
        }
    }

}

void Shape::createRandomTriangle() {
    m_width = Util::getRandInt(TRIANGLE_BASE_MIN, TRIANGLE_BASE_MAX);
    m_height = Util::getRandInt(TRIANGLE_HEIGHT_MIN, TRIANGLE_HEIGHT_MAX);
    m_x = Util::getRandInt(0, m_imageW-m_width/2);
    m_y = Util::getRandInt(0, m_imageH-m_height/2);
    m_color = Util::getRandomColor();
    m_angle = Util::getRandInt(0, 360);

}

void Shape::createRandomCube() {

}

void Shape::createRandomRectangle() {

}

