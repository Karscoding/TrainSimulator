//
// Created by karsh on 25-9-2024.
//

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "simulator.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


// Entry point
int main(int argc, char* args []) {
    Simulator sim = Simulator(SCREEN_WIDTH, SCREEN_HEIGHT);

    TTF_Init();

    TTF_Font *font = TTF_OpenFont("../resources/fonts/Roboto-Black.ttf", 32);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font,
                                                  "Hello World!", { 0xFF, 0xFF, 0xFF, 0 });
    SDL_Texture* texttext = SDL_CreateTextureFromSurface(sim.renderer, surface);
    SDL_Rect recttext = {10, 10, surface->w, surface->h};

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    SDL_Texture * texture = IMG_LoadTexture(sim.renderer, "../resources/VIRM.png");
    SDL_Rect destination;
    destination.h = 200;
    destination.w = 1000;
    destination.x = -500;
    destination.y = 380;

    sim.running = true;

    // sim loop
    while (sim.running) {

        // event handling
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT || e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
                sim.running = false;
            }
        }

        // clear the screen
        SDL_RenderClear(sim.renderer);
        // copy the texture to the rendering context
        SDL_RenderCopy(sim.renderer, texture, NULL, &destination);
        SDL_RenderCopy(sim.renderer, texttext, NULL, &recttext);
        SDL_RenderPresent(sim.renderer);
    }

    SDL_DestroyRenderer(sim.renderer);
    SDL_DestroyWindow(sim.window);
    SDL_Quit();
    return 0;
}
