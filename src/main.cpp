#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SDL2/SDL.h>
#include <random>
#include "Window.hpp"
#include "Geometrize.hpp"

int main(int argc, char **argv) {
    // initialize sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "error initializing sdl!\n";
        return -1;
    }

    // seed random number generator
    srand(time(NULL)); 

    if (argc > 1) {
        // create window and renderer
        SDL_Renderer *sdlrenderer;
        SDL_Window *sdlwindow;

        int error = SDL_CreateWindowAndRenderer(1920, 1080, SDL_WINDOW_RESIZABLE, &sdlwindow, &sdlrenderer);
        if (!sdlwindow || !sdlrenderer || error) {
            std::cerr << "error creating window or renderer!\n";
            return -1;
        }

        // read image
        cv::Mat image = cv::imread(argv[1]);
        // create window instance
        Window window(sdlwindow, sdlrenderer);
        Geometrize geometrize(image);
        while (window.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            
            geometrize.update();
            window.addShape(geometrize.getBestShape());
            window.drawImage(image);
            window.update();
        } 

        //cv::imwrite("test_out.jpg", image);
    }
    return 0;
}