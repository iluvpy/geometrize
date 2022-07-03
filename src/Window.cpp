#include "Window.hpp"

Window::Window(SDL_Window *window, SDL_Renderer *renderer) {
    m_window = window;
    m_renderer = renderer;
    m_running = true;
}

void Window::drawImage(cv::Mat image) {
    int width = image.cols;
    int height = image.rows;
    for (int y = 500; y < 600; y++) {
        for (int x = 500; x < 600; x++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);
            SDL_SetRenderDrawColor(m_renderer, (uint8_t)pixel[0], (uint8_t)pixel[1], (uint8_t)pixel[2], 255);
            SDL_RenderDrawPoint(m_renderer,x , y);
        }
    }    
}


bool Window::running() {
    return m_running;
}