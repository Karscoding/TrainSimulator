//
// Created by karsh on 25-9-2024.
//

#include <SDL.h>
#include <SDL_ttf.h>

#include "simulator.h"
#include "objectDrawer.h"
#include "objects/train.h"
#include <string>
#include "routes/routeTest.h"
#include "textDrawer.h"

Simulator::Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), currentRoute(nullptr), running(false) {
    this->window = SDL_CreateWindow("Train Simulator", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->mainFont = TTF_OpenFont("../resources/fonts/Roboto-Black.ttf", 32);

}

void Simulator::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_Quit();

    this->currentRoute = new RouteTest(*this);

    this->running = true;
}

void Simulator::run(int TICKDELAY) {
    // sim loop
    while (this->running) {
        Uint32 startTick = SDL_GetTicks();

        // event handling
        SDL_Event event;
        if ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                this->running = false;
            }
        }

        this->handleInput(event);


        // clear the screen
        SDL_RenderClear(this->renderer);


        // Render route objects
        this->screenTilePosition = ceil(this->screenPosition / SCREEN_WIDTH);

        ObjectDrawer::drawTiledMovingBackground(this->renderer, *this);


        for (Object *object : this->currentRoute->objectList) {
            ObjectDrawer::draw(object, this->renderer);
        }

        ObjectDrawer::draw(this->currentRoute->train, this->renderer);

        this->currentRoute->train->update();
        this->update();


        this->textDrawing();
        //        this->debugLog();

        SDL_RenderPresent(this->renderer);

        Uint32 tickTime = SDL_GetTicks() - startTick;
        if (TICKDELAY > tickTime)
        {
            //Wait remaining time
            SDL_Delay(TICKDELAY - tickTime);
        }
    }

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
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
           }
    }
}

void Simulator::update() {
    this->screenPosition += this->currentRoute->train->speed;
}

void Simulator::textDrawing() const {
    TextDrawer::drawTextFromString(*this->renderer, new std::string("Traction: "), this->mainFont, Vector2(15, 15));
    std::string message = std::to_string(this->currentRoute->train->traction_setting);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 15));

    TextDrawer::drawTextFromString(*this->renderer, new std::string("Braking: "), this->mainFont, Vector2(15, 50));
    message = std::to_string(this->currentRoute->train->braking_setting);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 50));

    TextDrawer::drawTextFromString(*this->renderer, new std::string("Speed: "), this->mainFont, Vector2(15, 80));
    message = std::to_string(this->currentRoute->train->speed_in_kmh);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 80));
}

void Simulator::debugLog() const {
    SDL_Log("Debug");
    SDL_Log("Traction Setting: %d", this->currentRoute->train->traction_setting);
    SDL_Log("Braking Setting: %d", this->currentRoute->train->braking_setting);
    SDL_Log("Speed: %f", this->currentRoute->train->speed);
}
