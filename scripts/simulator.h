//
// Created by karsh on 25-9-2024.
//

#ifndef TRAINSIMULATOR_SIMULATOR_H
#define TRAINSIMULATOR_SIMULATOR_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "routes/route.h"

struct Route;

// Is essentially a Main class with more appropriate naming
class Simulator {
public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Route *currentRoute;

    TTF_Font *mainFont;

    Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    bool running;
};

#endif //TRAINSIMULATOR_SIMULATOR_H
