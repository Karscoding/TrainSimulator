//
// Created by Shadow on 9/25/2024.
//

#include "route.h"
#include "../objects/signal.h"
#include "../objects/station.h"
#include "../objects/train.h"
#include "../placementScreen.h"
#include <typeinfo>

void Route::addObject(Object *object) {
    this->objectList.push_back(object);
}

void Route::addSignal(Signal *signal) {
    if (this->signalList.empty()) {
        this->nextSignal = signal;
    }
    this->signalList.push_back(signal);
}

void Route::addStation(Station *station) {
    this->stationList.push_back(station);
}


void Route::update() {

}

void Route::passSignal() {
    this->previousSignal = this->nextSignal;
    this->nextSignal = this->signalList.front();

    if (this->signalList.size() == 1) {
        return;
    } else {
        this->signalList.pop_front();
    }
}

void Route::changeNextSignal(Simulator &sim, int aspect) {
    this->signalList.remove(this->nextSignal);
    this->objectList.remove(this->nextSignal);
    this->nextSignal = Signal::createSignal(sim, this->nextSignal->position.x, aspect);
    this->addSignal(this->nextSignal);
    this->addObject(this->nextSignal);
}

Route* Route::createRouteBasedOnTiles(Simulator &sim, PlacementScreen *placementScreen) {
    auto* route = new Route();

    route->bg = new Object(sim, "../resources/Background.png", Vector2(0, 0));
    route->catenary = new Object(sim, "../resources/Bovenleiding.png", Vector2(0, 450));
    route->rail = new Object(sim, "../resources/Rails.png", Vector2(0, 848));
    route->train = new Train(sim, "../resources/VIRM.png", Vector2(-500, 650), 2, 3, 0.02);

    for (int i = 0; i < 10; i++) {
        if (!placementScreen->lightSignalTiles.empty()) {
            if (placementScreen->lightSignalTiles.find(i) != placementScreen->lightSignalTiles.end()) {
                route->addObject(placementScreen->lightSignalTiles.at(i));
                route->addSignal(placementScreen->lightSignalTiles.at(i));
            }
        }
        if (!placementScreen->signSignalTiles.empty()) {
            if (placementScreen->signSignalTiles.find(i) != placementScreen->signSignalTiles.end()) {
                route->addObject(placementScreen->signSignalTiles.at(i));
                route->addSignal(placementScreen->signSignalTiles.at(i));
            }
        }
        if (!placementScreen->stationTiles.empty()) {
            if (placementScreen->stationTiles.find(i) != placementScreen->stationTiles.end()) {
                route->addStation(placementScreen->stationTiles.at(i));
            }
        }
    }
    return route;
}
