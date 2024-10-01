//
// Created by karsh on 25-9-2024.
//

#include "simulator.h"
#include "objects/train.h"
#include <string>
#include "textDrawer.h"

Simulator::Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), currentRoute(nullptr), running(false) {
    this->window = SDL_CreateWindow("Train Simulator", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->mainFont = TTF_OpenFont("../resources/fonts/Roboto-Black.ttf", 32);
}

void Simulator::handleInput(SDL_Event &event) const {
    switch (event.type) {
        case SDL_KEYDOWN:
           switch (event.key.keysym.sym) {
               case SDLK_q:
                   this->currentRoute->train->increasePower();
                   break;
               case SDLK_a:
                   this->currentRoute->train->decreasePower();
                   break;
               case SDLK_e:
                   this->currentRoute->train->increaseBraking();
                   break;
               case SDLK_d:
                   this->currentRoute->train->decreaseBraking();
                   break;
               case SDLK_r:
                   this->currentRoute->train->resetPowerAndBraking();
                   break;
               default:
                   this->currentRoute->train->roll();
                   break;
           }
    }
}

void Simulator::textDrawing() const {
    TextDrawer::drawTextFromString(*this->renderer, new std::string("Traction: "), this->mainFont, Vector2(15, 15));
    std::string message = std::to_string(this->currentRoute->train->traction_setting);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 15));

    TextDrawer::drawTextFromString(*this->renderer, new std::string("Braking: "), this->mainFont, Vector2(15, 50));
    message = std::to_string(this->currentRoute->train->braking_setting);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 50));
}

void Simulator::debugLog() const {
    SDL_Log("Debug");
    SDL_Log("Traction Setting: %d", this->currentRoute->train->traction_setting);
    SDL_Log("Braking Setting: %d", this->currentRoute->train->braking_setting);
    SDL_Log("Speed: %f", this->currentRoute->train->speed);
}
