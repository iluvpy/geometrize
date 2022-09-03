#include <iostream>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <SDL2/SDL.h>
#include <random>
#include "Window.hpp"
#include "ThreadPool.hpp"


void updateGeometrize(ThreadPool *threadPool, Window *window);

int main(int argc, char **argv) {
    // initialize sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "error initializing sdl!\n";
        return -1;
    }

    // seed random number generator
    srand(time(NULL)); 

    if (argc > 1) {
        std::string imgPath = argv[1];
        FILE *imgFile;
        if ((imgFile = fopen(imgPath.c_str(), "r"))) {
            fclose(imgFile);
        } 
        else {
            std::cerr << "error occured trying to read file\n";
            return -1;
        }

        // read image
        cv::Mat image = cv::imread(argv[1]);
        // Geometrize geometrize(image);
        ThreadPool threadPool(image, 4);
        Window window(image.cols, image.rows);
        std::thread updateThr(updateGeometrize, &threadPool, &window);
        while (window.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            window.drawImage(threadPool.getShapeImage());
            window.update();
        } 
        window.close();
        std::cout << "closing...\n";
        updateThr.detach(); // wait till the thread finishes
        //cv::imwrite("test_out.jpg", image);
    }
    return 0;
}

// this will run in a seperate thread to avoid delaying the window event polling
void updateGeometrize(ThreadPool *geometrize, Window *window) {
    while (window->running()) {
        geometrize->update();
    }
}