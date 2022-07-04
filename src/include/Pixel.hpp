#pragma once
#include "Util.hpp"


typedef unsigned char uint8;

class Pixel {
public:
    Pixel();
    void setRandomColor();
    void setColor(uint8 r, uint8 g, uint8 b);
    void setValid(bool valid);
private:
    uint8 m_r;
    uint8 m_g;
    uint8 m_b;
    // used to decide if the pixel should be added to the image
    bool m_valid;
};