//
// Created by karsh on 25-9-2024.
//

#include <SDL.h>
#include <SDL_ttf.h>

#include "simulator.h"
#include "objectDrawer.h"
#include "objects/train.h"
#include "structs/object.h"
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
    this->placementScreen = new PlacementScreen(*this);

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

        // Render stuff dependent on what screen the player is on.
        if (currentScreen == Screens::PLACEMENT) {
            ObjectDrawer::draw(this->placementScreen->placementScreenBG, this->renderer);
            drawTiles();
        } else if (currentScreen == Screens::OPTIONS) {
            ObjectDrawer::draw(this->placementScreen->optionsScreenBG, this->renderer);
            drawTiles();
        } else if (currentScreen == Screens::DRIVING) {
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
//
//            for (Station *station : this->currentRoute->stationList) {
//                int temp = station->rect.x;
//                station->rect.x -= (int) this->screenPosition;
//                for (int i = 0; i < station->tileSpan; i++) {
//                    int temp2 = station->rect.x;
//                    station->rect.x += i * 1280;
//                    ObjectDrawer::draw(station, this->renderer);
//                    station->rect.x = temp2;
//                }
//                station->rect.x = temp;
//            }

            // Update functions
            this->train->update(*this);
            this->update();


            this->textDrawing();
            //        this->debugLog();
        }



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

void Simulator::handleInput(SDL_Event &event) {
    if (currentScreen == Screens::DRIVING) {
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
                    case SDLK_SPACE:
                        currentScreen = Screens::PLACEMENT;
                        break;
                }
        }
    } else if (currentScreen == Screens::PLACEMENT || currentScreen == Screens::OPTIONS) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN) {
                    this->currentRoute = Route::createRouteBasedOnTiles(*this, this->placementScreen);
                    currentScreen = Screens::DRIVING;
                } else if (this->placementScreen->selected == -1) {
                    this->placementScreen->selected = (int) event.key.keysym.sym - 48;
                    if (this->placementScreen->selected == 0) {
                        this->placementScreen->selected = 10;
                    }
                    this->currentScreen = Screens::OPTIONS;
                } else {
                    switch (event.key.keysym.sym) {
                        case SDLK_1:
                            this->placementScreen->lightSignalTiles.insert_or_assign(this->placementScreen->selected, Signal::createSignal(
                                    *this, (this->placementScreen->selected * 4000) - 3500, LightAspects::GREEN));
                            break;
                        case SDLK_2:
                            this->placementScreen->lightSignalTiles.insert_or_assign(this->placementScreen->selected, Signal::createSignal(
                                    *this, (this->placementScreen->selected * 4000) - 3500, LightAspects::YELLOW));
                            break;
                        case SDLK_3:
                            this->placementScreen->lightSignalTiles.insert_or_assign(this->placementScreen->selected, Signal::createSignal(
                                    *this, (this->placementScreen->selected * 4000) - 3500, LightAspects::RED));
                            break;
                        case SDLK_4:
                            this->placementScreen->signSignalTiles.insert_or_assign(this->placementScreen->selected, Signal::createSignal(
                                    *this, (this->placementScreen->selected * 4000) - 4000, SignAspects::VMAX_40));
                            break;
                        case SDLK_5:
                            this->placementScreen->signSignalTiles.insert_or_assign(this->placementScreen->selected, Signal::createSignal(
                                    *this, (this->placementScreen->selected * 4000) - 4000, SignAspects::VMAX_130));
                            break;
                        case SDLK_6:
                            if (this->placementScreen->stationTiles.find(this->placementScreen->selected) == this->placementScreen->stationTiles.end()) {
                                this->placementScreen->stationTiles.insert_or_assign(this->placementScreen->selected, new Station(
                                        *this, (this->placementScreen->selected * 4000) - 3500, 3));
                            } else {
                                this->placementScreen->stationTiles.erase(this->placementScreen->selected);
                            }
                            break;
                    }
                    this->placementScreen->selected = -1;
                    this->currentScreen = Screens::PLACEMENT;
                }
        }
    }

}

void Simulator::drawTiles() {
    for (int i = 0; i < 11; i++) {
        if (!placementScreen->lightSignalTiles.empty()) {
            if (placementScreen->lightSignalTiles.find(i) != placementScreen->lightSignalTiles.end()) {
                Object object = *this->placementScreen->lightSignalTiles.at(i);
                if (i == 0) {
                    object.rect.x = 1630;
                } else {
                    object.rect.x = (i * 165) - 50;
                }
                object.rect.w = 100;
                object.rect.h = 200;
                object.rect.y = 650;
                ObjectDrawer::draw(&object, this->renderer);
            }
        }
        if (!placementScreen->signSignalTiles.empty()) {
            if (placementScreen->signSignalTiles.find(i) != placementScreen->signSignalTiles.end()) {
                Object object = *this->placementScreen->signSignalTiles.at(i);
                if (i == 0) {
                    object.rect.x = 1630;
                } else {
                    object.rect.x = (i * 175) - 70;
                }
                object.rect.w = 100;
                object.rect.h = 200;
                object.rect.y = 650;
                ObjectDrawer::draw(&object, this->renderer);
            }
        }
        if (!placementScreen->stationTiles.empty()) {
            if (placementScreen->stationTiles.find(i) != placementScreen->stationTiles.end()) {
                Object object = *this->placementScreen->stationTiles.at(i);
                if (i == 0) {
                    object.rect.x = 1630;
                } else {
                    object.rect.x = (i * 175) - 50;
                }
                object.rect.w = 100;
                object.rect.h = 200;
                object.rect.y = 650;
                ObjectDrawer::draw(&object, this->renderer);
            }
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


    color = COLOR_BLACK;
    TextDrawer::drawTextFromString(*this->renderer,new std::string("Distance next stop: "),this->mainFont,Vector2(15, 170), color);
    message = std::to_string(this->train->distance_next_station_end);
    message = message.substr(0, 5);
    TextDrawer::drawTextFromString(*this->renderer, &message, this->mainFont, Vector2(300, 170), color);
}

// Not currently used
void Simulator::debugLog() const {
    SDL_Log("Debug");
    SDL_Log("Traction Setting: %d", this->train->traction_setting);
    SDL_Log("Braking Setting: %d", this->train->braking_setting);
    SDL_Log("Speed: %f", this->train->speed);
}
