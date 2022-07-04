#include "Window.hpp"


Window::Window(SDL_Window *window, SDL_Renderer *renderer) {
    m_window = window;
    m_renderer = renderer;
    m_running = true;
    m_lastImageDrawn = 0.0;
    SDL_SetWindowTitle(m_window, "Geometrize");
}

void Window::drawImage(cv::Mat image) {
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);

    // if at least IMAGE_DRAW_INTERVAL seconds have passed since last image draw
    double now = clock();
    float time = now - m_lastImageDrawn;

    if (time > IMAGE_DRAW_INTERVAL) {
        int width = image.cols;
        int height = image.rows;
        for (int y = 0; y < height-1; y++) {
            for (int x = 0; x < width-1; x++) {
                cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);
                SDL_SetRenderDrawColor(m_renderer, (uint8_t)pixel[0], (uint8_t)pixel[1], (uint8_t)pixel[2], 255);
                SDL_RenderDrawPoint(m_renderer, x, y);
            }
        } 
        m_lastImageDrawn = clock(); 
    }
    
    SDL_RenderPresent(m_renderer);

}


void Window::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_running = false;
        }
    }

}


bool Window::running() {
    return m_running;
}


double Window::clock() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
