#include <cstdio>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void fail(const char* reason);

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

int main() {
    SDL_Window* window = nullptr;
    SDL_Surface* screen_surface = nullptr;

    init(window, screen_surface);

    SDL_FillRect(screen_surface,
                 nullptr,
                 SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

    // The window needs to be updated before anything will show.
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void fail(const char* reason) {
    printf("%s", reason);
    EXIT_FAILURE;
}