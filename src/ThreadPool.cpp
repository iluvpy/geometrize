#include "ThreadPool.hpp"

ThreadPool::ThreadPool(const cv::Mat& originalImage, int threads) {
    m_originalImage = originalImage;
    m_shapeImage = m_originalImage.clone();
    m_numThreads = threads;
    m_generation = 0;


    int width = m_originalImage.cols;
    int height = m_originalImage.rows;

    // calculate average the pixel value of the original image and set the 
    // shape image background to that average
    double b_sum = 0.0;
    double g_sum = 0.0;
    double r_sum = 0.0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            b_sum += m_originalImage.at<cv::Vec3b>(i, j)[0]; 
            g_sum += m_originalImage.at<cv::Vec3b>(i, j)[1]; 
            r_sum += m_originalImage.at<cv::Vec3b>(i, j)[2]; 
        }
    }

    int pixels = width*height;
    b_sum /= pixels;
    g_sum /= pixels;
    r_sum /= pixels;

    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            m_shapeImage.at<cv::Vec3b>(i, j)[0] = b_sum; 
            m_shapeImage.at<cv::Vec3b>(i, j)[1] = g_sum; 
            m_shapeImage.at<cv::Vec3b>(i, j)[2] = r_sum; 
        }
    }


    for (int i = 0; i < m_numThreads; i++) {
        m_gInstances.push_back(Geometrize(m_originalImage, m_shapeImage));
        m_threads.push_back(std::thread(&ThreadPool::updateThr, this, &m_gInstances[i]));
    }
}

void ThreadPool::update() {
    m_generation++;
    // checking if every thread finished its current generation
    for (;;) {
        for (const auto& gInstance : m_gInstances) {
            if (gInstance.getGeneration() != m_generation) {
                Util::sleep(5);
                continue;
            } 
        }
        break;
    }
    double score = 0.0;
    Shape bestShape;
    for (const auto& gInstance : m_gInstances) {
        Shape gInstanceShape = gInstance.getCurrentBestShape();
        if (score > gInstanceShape.getScore()) {
            score = gInstanceShape.getScore();
            bestShape = gInstanceShape;
        }
    }
    bestShape.addShapeToImage(m_shapeImage);
    cv::imwrite("shape_image.png", m_shapeImage);
    
}

void ThreadPool::updateThr(Geometrize *gInstance) {
    for (;;) {
        if (gInstance->getGeneration()+1 == m_generation) {
            gInstance->update();
        }
        Util::sleep(10);
    }
}

cv::Mat ThreadPool::getShapeImage() {
    return m_shapeImage;
}
