//
// Created by karsh on 25-9-2024.
//

// SDL Includes
#include <SDL.h>

// Internal Includes
#include "simulator.h"

Simulator::Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT) {
    this->window = SDL_CreateWindow("Train Simulator", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}
