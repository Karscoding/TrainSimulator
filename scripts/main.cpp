#include <SDL.h>
#include <SDL_image.h>


#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char* args []) {
    // variable declarations
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;

    bool running = false;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;


    // create the window and renderer
    // note that the renderer is accelerated
    win = SDL_CreateWindow("Train Simulator", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture * texture = IMG_LoadTexture(renderer, "../resources/VIRM.png");
    SDL_Rect destination;
    destination.h = 200;
    destination.w = 1000;
    destination.x = -500;
    destination.y = 380;

    running = true;

    // main loop
    while (running) {

        // event handling
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT || e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        // clear the screen
        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, texture, NULL, &destination);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
