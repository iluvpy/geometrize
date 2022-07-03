#include "Window.hpp"

Window::Window(SDL_Window *window, SDL_Renderer *renderer) {
    m_window = window;
    m_renderer = renderer;
    m_running = true;

    SDL_SetWindowTitle(m_window, "Geometrize");
}

void Window::drawImage(cv::Mat image) {
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);

    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 600; x++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);
            SDL_SetRenderDrawColor(m_renderer, (uint8_t)pixel[0], (uint8_t)pixel[1], (uint8_t)pixel[2], 255);
            SDL_RenderDrawPoint(m_renderer, x, y);
        }
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