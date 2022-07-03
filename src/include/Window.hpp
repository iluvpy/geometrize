#pragma once
#include <SDL2/SDL.h>
#include <opencv2/core.hpp>

class Window {
public:
    Window(SDL_Window *window, SDL_Renderer *renderer);
    void drawImage(cv::Mat image);
    void update();
    bool running();
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_running;
};