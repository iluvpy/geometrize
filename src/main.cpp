#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SDL2/SDL.h>

#include "Window.hpp"

int main(int argc, char **argv) {
    if (SDL_Init(NULL) < 0) {
        std::cerr << "error initializing sdl!\n";
        return -1;
    }

    if (argc > 1) {
        SDL_Renderer *sdlrenderer;
        SDL_Window *sdlwindow;
        int error = SDL_CreateWindowAndRenderer(1920, 1080, NULL, &sdlwindow, &sdlrenderer);
        if (!sdlwindow || !sdlrenderer || error) {
            std::cerr << "error creating window or renderer!\n";
            return -1;
        }
        cv::Mat image = cv::imread(argv[1]);

        Window window(sdlwindow, sdlrenderer);

        while (window.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            window.drawImage(image);
        }       
        
        cv::imwrite("test_out.jpg", image);
    }
    return 0;
}