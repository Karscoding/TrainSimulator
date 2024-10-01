//
// Created by karsh on 25-9-2024.
//

#include <SDL.h>
#include <SDL_ttf.h>

#include "simulator.h"
#include "objectDrawer.h"
#include "structs/object.h"
#include "routes/routeTest.h"
#include "objects/train.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Entry point
int main(int argc, char* args []) {
    TTF_Init();

    Simulator sim = Simulator(SCREEN_WIDTH, SCREEN_HEIGHT);


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    sim.currentRoute = new RouteTest(sim);

    sim.running = true;

    // sim loop
    while (sim.running) {
        // event handling
        SDL_Event event;
        if ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                sim.running = false;
            }
        }

        sim.handleInput(event);


        // clear the screen
        SDL_RenderClear(sim.renderer);

        // Render route objects
        for (Object *object : sim.currentRoute->objectList) {
            ObjectDrawer::draw(object, sim.renderer);
        }

        ObjectDrawer::draw(sim.currentRoute->train, sim.renderer);


        sim.textDrawing();
//        sim.debugLog();

        SDL_RenderPresent(sim.renderer);
    }

    SDL_DestroyRenderer(sim.renderer);
    SDL_DestroyWindow(sim.window);
    SDL_Quit();
    return 0;
}
