#include "Window.hpp"


Window::Window(SDL_Window *window, SDL_Renderer *renderer) {
    m_window = window;
    m_renderer = renderer;
    m_running = true;
    m_lastImageDrawn = 0.0;
    SDL_SetWindowTitle(m_window, "Geometrize");
}

void Window::drawImage(cv::Mat image) {
    double now = clock();
    if (now-m_lastImageDrawn > IMAGE_DRAW_INTERVAL) {
        SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
        SDL_RenderClear(m_renderer);
        int width = image.cols;
        int height = image.rows;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
                SDL_SetRenderDrawColor(m_renderer, pixel[0], pixel[1], pixel[2], 255);
                SDL_RenderDrawPoint(m_renderer, j, i);
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

