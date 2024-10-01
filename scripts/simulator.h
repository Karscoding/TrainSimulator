//
// Created by karsh on 25-9-2024.
//

#ifndef TRAINSIMULATOR_SIMULATOR_H
#define TRAINSIMULATOR_SIMULATOR_H

#include <SDL_ttf.h>
#include <SDL.h>

#include "routes/route.h"

// Is essentially a Main class with more appropriate naming
class Simulator {
public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    float screenPosition = 0;
    int screenTilePosition;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Route *currentRoute;

    TTF_Font *mainFont;

    Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT);

    void update();

    void handleInput(SDL_Event &event) const;

    void textDrawing() const;
    void debugLog() const;

    bool running;
};

#endif //TRAINSIMULATOR_SIMULATOR_H
