//
// Created by karsh on 25-9-2024.
//

#include <SDL_ttf.h>
#include <thread>

#include "simulator/simulator.h"
#include "ai/ai.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TICKRATE 60
#define TICKDELAY (1000 / TICKRATE)

// Entry point
int main(int argc, char* args []) {
    TTF_Init();

    Simulator sim = Simulator(SCREEN_WIDTH, SCREEN_HEIGHT);
    sim.initialize();
    AI ai = AI(sim.currentRoute->train, 140);

    std::thread aiThread(&AI::run, &ai);
    sim.run(TICKDELAY);

    ai.close();

    return 0;
}
