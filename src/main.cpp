#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SDL2/SDL.h>
#include <random>
#include "Window.hpp"
#include "Geometrize.hpp"


void updateGeometrize(Geometrize *geometrize, Window *window);

int main(int argc, char **argv) {
    // initialize sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "error initializing sdl!\n";
        return -1;
    }

    // seed random number generator
    srand(time(NULL)); 

    if (argc > 1) {
        // read image
        cv::Mat image = cv::imread(argv[1]);
        Geometrize geometrize(image);
        Window window;
        std::thread updateThr(updateGeometrize, &geometrize, &window);
        while (window.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            window.drawImage(geometrize.getShapeImage());
            window.update();
        } 
        window.close();
        std::cout << "closing...\n";
        updateThr.join(); // wait till the thread finishes
        //cv::imwrite("test_out.jpg", image);
    }
    return 0;
}

// this will run in a seperate thread to avoid delaying the window event polling
void updateGeometrize(Geometrize *geometrize, Window *window) {
    while (window->running()) {
        geometrize->update();
    }
}