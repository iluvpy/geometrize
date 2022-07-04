#pragma once
#include "Util.hpp"
#include "Color.hpp"

class Pixel {
public:
    Pixel();
    void setRandomColor();
    void setColor(const Color& color);
    void setValid(bool valid);
    bool isValid();
private:
    Color m_color;
    // used to decide if the pixel should be added to the image
    bool m_valid;
};