#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <opencv2/core.hpp>
#include <ctime>
#include <chrono>
#include "Shape.hpp"

#define IMAGE_DRAW_INTERVAL 1.0f

class Window {
public:
    Window(SDL_Window *window, SDL_Renderer *renderer);
    void drawImage(cv::Mat image);
    void update();
    bool running();
    double clock();
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_running;
    double m_lastImageDrawn;
};