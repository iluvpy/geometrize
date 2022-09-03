#pragma once

#include "Geometrize.hpp"
#include <thread>

class ThreadPool {
public:
    ThreadPool(const cv::Mat& originalImage, int threads);
    void update();
    cv::Mat getShapeImage();
private:
    int m_numThreads;
    int m_generation;
    cv::Mat m_originalImage;
    cv::Mat m_shapeImage;
    std::vector<std::thread> m_threads;
    std::vector<Geometrize> m_gInstances;

    void updateThr(Geometrize *gInstance);
};