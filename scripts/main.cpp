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

#define TICKRATE 60
#define TICKDELAY 1000 / TICKRATE

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
        Uint32 startTick = SDL_GetTicks();

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
        sim.screenTilePosition = ceil(sim.screenPosition / SCREEN_WIDTH);

        ObjectDrawer::drawTiledMovingBackground(sim.renderer, sim);


        for (Object *object : sim.currentRoute->objectList) {
            ObjectDrawer::draw(object, sim.renderer);
        }

        ObjectDrawer::draw(sim.currentRoute->train, sim.renderer);

        sim.currentRoute->train->update();
        sim.update();


        sim.textDrawing();
//        sim.debugLog();

        SDL_RenderPresent(sim.renderer);

        Uint32 tickTime = SDL_GetTicks() - startTick;
        if (TICKDELAY > tickTime)
        {
            //Wait remaining time
            SDL_Delay(TICKDELAY - tickTime);
        }
    }

    SDL_DestroyRenderer(sim.renderer);
    SDL_DestroyWindow(sim.window);
    SDL_Quit();
    return 0;
}
