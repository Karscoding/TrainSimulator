#include "ai.h"

AI::AI(Train *train, float targetSpeed)
    : train(train), targetSpeed(targetSpeed) {}

void AI::run() {
    running = true;

    int counter = 0;

    while (running) {
        switch (this->currentTask) {
            case Task::ACCELERATE:
                if (!train->doors_opened && train->speed_in_kmh <= this->targetSpeed - 3) {
                    if (train->traction_setting < 7) {
                        train->increasePower();
                    }
                } else if (train->speed_in_kmh > targetSpeed) {
                    train->decreasePower();
                    if (counter > 500) {
                        this->currentTask = Task::DECCELERATE;
                    } else {
                        counter++;
                    }
                }
                break;
            case Task::DECCELERATE:
                if (train->speed_in_kmh > this->targetSpeed - 5) {
                    if (train->braking_setting < 2) {
                        train->increaseBraking();
                    }
                } else if (train->speed_in_kmh > this->targetSpeed - 10) {
                    if (train->braking_setting < 3) {
                        train->increaseBraking();
                    }
                } else if (train->speed_in_kmh > 20) {
                    if (train->braking_setting < 5) {
                        train->increaseBraking();
                    }
                } else if (train->speed_in_kmh > 10){
                    if (train->braking_setting > 2) {
                        train->decreaseBraking();
                    }
                } else if (train->speed_in_kmh > 2) {
                    if (train->braking_setting > 1) {
                        train->decreaseBraking();
                    }
                }
                break;
        }
    }
}

void AI::close() {
    running = false;
}