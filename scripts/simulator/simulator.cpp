//
// Created by karsh on 25-9-2024.
//

#include <SDL.h>
#include <SDL_ttf.h>

#include "simulator.h"
#include "objectDrawer.h"
#include "objects/train.h"
#include "objects/signal.h"
#include "objects/station.h"
#include <cmath>
#include <string>
#include "routes/routeTest.h"
#include "textDrawer.h"

#define COLOR_BLACK SDL_Color(0, 0, 0, 0)

Simulator::Simulator(int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), currentRoute(nullptr), running(false), train(nullptr) {
    this->window = SDL_CreateWindow("Train Simulator", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_MaximizeWindow(this->window);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->mainFont = TTF_OpenFont("../resources/fonts/Roboto-Black.ttf", 32);
}

/*
 * Setup before the simulator runs
 */
void Simulator::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_Quit();

    this->currentRoute = new RouteTest(*this);
    this->train = this->currentRoute->train;

    this->running = true;
}

/*
 *
 * Simulator-loop
 * Runs every tick and performs everything that needs to be
 * executed during every tick
 *
 * */
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


        // Calculate position in tiles
        this->screenTilePosition = std::ceil(this->screenPosition / (float) SCREEN_WIDTH);


        // Render background objects that move with the tiles
        ObjectDrawer::drawTiledMovingBackground(this->renderer, *this);

        // Render train
        ObjectDrawer::draw(this->train, this->renderer);

        // Render the rest of the objects on the route
        for (Object *object : this->currentRoute->objectList) {
            int temp = object->rect.x;
            object->rect.x -= (int) this->screenPosition;
            ObjectDrawer::draw(object, this->renderer);
            object->rect.x = temp;
        }

        for (Station *station : this->currentRoute->stationList) {
            int temp = station->rect.x;
            for (int i = 0; i < station->tileSpan; i++) {
                station->rect.x -= (int) this->screenPosition;
                station->rect.x += i * 1280;
                ObjectDrawer::draw(station, this->renderer);
            }
            station->rect.x = temp;
        }

        // Update functions
        this->train->update(*this);
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
                    this->train->increasePower();
                    break;
                case SDLK_a:
                    this->train->decreasePower();
                    break;
                case SDLK_e:
                    this->train->increaseBraking();
                    break;
                case SDLK_d:
                    this->train->decreaseBraking();
                    break;
                case SDLK_r:
                    this->train->resetPowerAndBraking();
                    break;
                case SDLK_BACKSPACE:
                    this->train->applyEmergencyBraking();
                    break;
           }
    }
}

void Simulator::update() {
    this->screenPosition += this->train->speed;
}

/*
 * Text drawing on the screen
 */
void Simulator::textDrawing() const {
    SDL_Color color;

    // Traction-setting information:

    // Color of text (Green or Black)
    if (this->train->traction_setting > 0) {
        color = SDL_Color(0, 153, 51, 255);
    } else {
        color = COLOR_BLACK;
    }

    // Rendering Traction-setting information
    TextDrawer::drawTextFromString(*this->renderer,new std::string("Traction: "),this->mainFont,Vector2(15, 15), color);
    std::string value = std::to_string(this->train->traction_setting);
    TextDrawer::drawTextFromString(*this->renderer, &value, this->mainFont, Vector2(150, 15), color);


    // Braking-setting information:

    // Color of text (Red or Black)
    if (this->train->braking_setting > 0) {
        color = SDL_Color(204, 51, 0, 255);
    } else {
        color = COLOR_BLACK;
    }

    // Rendering Braking-setting information
    TextDrawer::drawTextFromString(*this->renderer,new std::string("Braking: "),this->mainFont,Vector2(15, 50), color);
    value = std::to_string(this->train->braking_setting);
    TextDrawer::drawTextFromString(*this->renderer, &value, this->mainFont, Vector2(150, 50), color);


    // Speed information:

    // Color of text (Red or Black)
    if (this->train->speeding) {
        color = SDL_Color(204, 51, 0, 255);
    } else {
        color = COLOR_BLACK;
    }

    // Rendering Current Speed
    TextDrawer::drawTextFromString(*this->renderer,new std::string("Speed: "),this->mainFont,Vector2(15, 80), color);
    std::string message = std::to_string(this->train->speed_in_kmh);
    message = message.substr(0, 4);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(150, 80), color);

    // Rendering Speed limit information
    TextDrawer::drawTextFromString(*this->renderer, new std::string("Speed Limit: "), this->mainFont, Vector2(15, 110), color);
    std::string max_speed;
    if (this->train->previousSignal == nullptr) {
        max_speed = std::to_string(this->currentRoute->startAspect);
    } else {
        max_speed = std::to_string(this->train->current_vmax);
    }
    TextDrawer::drawTextFromString(*this->renderer, &max_speed, this->mainFont, Vector2(200, 110), color);


    if (this->train->doors_opened) {
        color = SDL_Color(0, 153, 51, 255);
    } else {
        color = COLOR_BLACK;
    }
    TextDrawer::drawTextFromString(*this->renderer, new std::string("Doors"), this->mainFont, Vector2(15, 140), color);

}

// Not currently used
void Simulator::debugLog() const {
    SDL_Log("Debug");
    SDL_Log("Traction Setting: %d", this->train->traction_setting);
    SDL_Log("Braking Setting: %d", this->train->braking_setting);
    SDL_Log("Speed: %f", this->train->speed);
}
