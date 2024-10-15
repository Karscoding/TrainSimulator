//
// Created by Shadow on 9/25/2024.
//

#include "route.h"

void Route::addObject(Object *object) {
    this->objectList.push_back(object);
}

void Route::addSignal(Signal *signal) {
    if (this->signalList.empty()) {
        this->nextSignal = signal;
    }
    this->signalList.push_back(signal);
}


void Route::update() {

}

void Route::passSignal() {
    this->nextSignal = this->signalList.front();
    this->signalList.pop_front();
}