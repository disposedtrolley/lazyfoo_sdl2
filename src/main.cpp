#include <cstdio>
#include <vector>
#include <string>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void fail(const std::string& reason);

void init(SDL_Window*& window, SDL_Surface*& screen_surface) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        char* error;
        asprintf(&error, "SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
        fail(error);
    }

    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        char* error;
        asprintf(&error, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        fail(error);
    }

    screen_surface = SDL_GetWindowSurface(window);
}

SDL_Surface* load_surface(const std::string& path) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == nullptr) {
        char* error;
        asprintf(&error, "Unable to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        fail(error);
    }

    return surface;
}

void close(const std::vector<SDL_Surface*>& surfaces, SDL_Window* window) {
    for (auto&& surface : surfaces) {
        SDL_FreeSurface(surface);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;

    init(window, screen_surface);
    SDL_Surface* hello_world = load_surface("hello_world.bmp");

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        // Keep popping events off the queue until empty (SDL_PollEvent()
        // returns 0 in this case).
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN) {
                quit = true;
            }
        }

        SDL_BlitSurface(hello_world, nullptr, screen_surface, nullptr);

        // UpdateWindowSurface copies the contents of the back buffer into the
        // front buffer. Most rendering systems are double buffered in this way
        // to allow for programs to draw incrementally without an incomplete frame
        // being displayed on the screen.
        SDL_UpdateWindowSurface(window);
    }

    close(std::vector<SDL_Surface*>{screen_surface, hello_world}, window);
    return EXIT_SUCCESS;
}

void fail(const std::string& reason) {
    printf("%s", reason.c_str());
}