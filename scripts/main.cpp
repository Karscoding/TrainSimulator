#include <SDL.h>
#include <SDL_image.h>


#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "/girlypop.png"

int main(int argc, char* args []) {
    // variable declarations
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    IMG_Init(IMG_INIT_PNG);

    // create the window and renderer
    // note that the renderer is accelerated
    win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface * image = IMG_Load("girlypop.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    // main loop
    while (1) {

        // event handling
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT)
                break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }

        // clear the screen
        SDL_RenderClear(renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
