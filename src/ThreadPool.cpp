#include "ThreadPool.hpp"
#include "Debug.hpp"



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
        Geometrize gInstance(m_originalImage, m_shapeImage);
        m_gInstances.push_back(gInstance);
        m_threads.push_back(std::thread(&ThreadPool::updateThr, this, i));
    }
}

void ThreadPool::update() {
    std::cout << "ThreadPool::update was called!\n";
    m_generation++;
    // checking if every thread finished its current generation
    bool threadsFinished = false;
    while (!threadsFinished) {
        for (const auto& gInstance : m_gInstances) {
            if (gInstance.getGeneration() != m_generation) {
                Util::sleep(10);
                break;
            } 
            threadsFinished = true;
        }
    }

    std::cout << "all threads finished updating!\n"; 

    double score = 0.0;
    Shape bestShape;
    for (const auto& gInstance : m_gInstances) {
        Shape gInstanceShape = gInstance.getCurrentBestShape();
        if (gInstanceShape.getScore() > score) {
            score = gInstanceShape.getScore();
            bestShape = gInstanceShape;
        }
    }
    
    bestShape.addShapeToImage(m_shapeImage);
    cv::imwrite("shape_image.png", m_shapeImage);

    for (auto& gInstance : m_gInstances) {
        gInstance.setShapeImage(m_shapeImage);
    }
    
}


void ThreadPool::updateThr(int threadNumber) {
    auto id = std::this_thread::get_id();
    for (;;) {
        /** 
         * when the threadpool updates the generation is increased by 1, thus calling the update (here) function 
         * making this thread wait until the treadpool updates again 
        */
        if (m_gInstances[threadNumber].getGeneration()+1 == m_generation) {
            std::cout << "calling Geometrize::update from: " << id << std::endl;
            m_gInstances[threadNumber].update();
        }
        Util::sleep(100);
    }
}

cv::Mat ThreadPool::getShapeImage() {
    return m_shapeImage;
}
