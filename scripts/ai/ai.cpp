#include "ai.h"

AI::AI(Train *train, float targetSpeed)
    : train(train), targetSpeed(targetSpeed) {}

void AI::run() {
    running = true;

    while (running) {
        this->update();
    }
}

void AI::update() {
    switch (this->currentTask) {
        case Task::ACCELERATE:
            train->setBraking(0);
            if (!train->doors_opened && train->speed_in_kmh <= this->targetSpeed - 3) {
                train->setPower(7);
                this->targetSpeed = train->nextSignal->currentAspect;
            } else if (train->speeding || train->speed_in_kmh > targetSpeed) {
                train->setPower(0);
                this->targetSpeed = (float) train->nextSignal->currentAspect;
                this->currentTask = Task::COASTING;
            }
            break;
        case Task::COASTING:
            if (train->speeding) {
                train->setPower(0);
                train->setBraking(1);
            } else if (train->speed_in_kmh > this->targetSpeed + 2) {
                train->setBraking(0);
                train->setPower(0);
            } else if (train->speed_in_kmh < this->targetSpeed - 2) {
                train->setBraking(0);
                train->setPower(2);
            }
            break;
        case Task::DECCELERATE:
            if (train->speed_in_kmh > this->targetSpeed - 5) {
                train->setBraking(2);
            } else if (train->speed_in_kmh > this->targetSpeed - 10) {
                train->setBraking(3);
            } else if (train->speed_in_kmh > 10) {
                train->setBraking(5);
            } else if (train->speed_in_kmh > 5){
                train->setBraking(2);
            } else if (train->speed_in_kmh > 2) {
                train->setBraking(1);
            }
            break;
    }
}

void AI::close() {
    running = false;
}