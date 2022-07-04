#include "Geometrize.hpp"


Geometrize::Geometrize(const cv::Mat& image) {
    m_originalImage = image;
    m_image = image;
}