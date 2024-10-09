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
                    train->setPower(7);
                } else if (train->speed_in_kmh > targetSpeed) {
                    train->setPower(0);
                    if (counter > 500) {
                        this->currentTask = Task::DECCELERATE;
                    } else {
                        counter++;
                    }
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
}

void AI::close() {
    running = false;
}