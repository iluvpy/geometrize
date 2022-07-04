#include "Pixel.hpp"


Pixel::Pixel() {
    m_color = Color{0, 0, 0};
    m_valid = true;
}

void Pixel::setRandomColor() {
    m_color = Color{(uint8)Util::getRandInt(0, 255), (uint8)Util::getRandInt(0, 255), (uint8)Util::getRandInt(0, 255)};
}

void Pixel::setValid(bool valid) {
    m_valid = valid;
}

void Pixel::setColor(const Color& color) {
    m_color = color;
}

bool Pixel::isValid() {
    return m_valid;
}

