//
// Created by karsh on 25-9-2024.
//

#include "simulator.h"
#include "objects/train.h"

Simulator::Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), currentRoute(nullptr), running(false) {
    this->window = SDL_CreateWindow("Train Simulator", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->mainFont = TTF_OpenFont("../resources/fonts/Roboto-Black.ttf", 32);
}

void Simulator::handleInput() const {
    const Uint8* keyboard;
    SDL_PumpEvents();
    keyboard = SDL_GetKeyboardState(nullptr);
    if (keyboard[SDLK_q]) {
        this->currentRoute->train->speed = 50;
    }
}
