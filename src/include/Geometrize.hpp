#pragma once
#include <opencv2/core.hpp>

class Geometrize {
public:
    Geometrize(const cv::Mat& image);

private:
    cv::Mat m_originalImage;
    cv::Mat m_image;
    
};