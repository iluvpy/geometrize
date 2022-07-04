#include "Pixel.hpp"


Pixel::Pixel() {
    m_r = 0;
    m_g = 0;
    m_b = 0;
}

void Pixel::setRandomColor() {
    m_r = Util::getRandInt(0, 255);
    m_g = Util::getRandInt(0, 255);
    m_b = Util::getRandInt(0, 255);
}

void Pixel::setValid(bool valid) {
    m_valid = valid;
}

void Pixel::setColor(uint8 r, uint8 g, uint8 b) {
    m_r = r;
    m_g = g;
    m_b = b;
}
