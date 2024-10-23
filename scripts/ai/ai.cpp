#include "ai.h"
#include <chrono>
#include <thread>

#define MS_DELAY 100

AI::AI(Train *train, float maxSpeed)
    : train(train), maxSpeed(maxSpeed) {}

void AI::run() {
    running = true;

    while (running) {
        this->update();
    }
}

void AI::update() {
    this->decideTask();
    switch (this->currentTask) {
        case Task::ACCELERATE:
            train->setBraking(0);
            if (train->speeding || train->speed_in_kmh > maxSpeed - 3) {
                train->setPower(0);

                if (train->previousSignal != nullptr) {
                    this->maxSpeed = (float) train->previousSignal->currentAspect;
                } else {
                    this->maxSpeed = (float) train->current_vmax;
                }

                this->currentTask = Task::COASTING;
            } else if (!train->doors_opened && train->speed_in_kmh <= this->maxSpeed - 3) {
                train->setPower(7);
            }
            break;
        case Task::COASTING:
            if (train->speeding) {
                currentTask = Task::DECCELERATE_TO_LIMIT;
            } else if (train->speed_in_kmh > this->maxSpeed + 2) {
                train->setBraking(0);
                train->setPower(0);
            } else if (train->speed_in_kmh < this->maxSpeed - 2) {
                train->setBraking(0);
                train->setPower(2);
            }
            break;
        case Task::DECCELERATE_TO_LIMIT:
            train->setPower(0);
            if (train->speed_in_kmh > this->maxSpeed + 10) {
                train->setBraking(3);
            } else if (train->speed_in_kmh > this->maxSpeed + 5) {
                train->setBraking(2);
            } else if (train->speed_in_kmh > this->maxSpeed - 3) {
                train->setBraking(1);
            } else if (train->speed_in_kmh < this->maxSpeed) {
                train->setBraking(0);
                decideTask();
            }
            break;
        case Task::DECCELERATE_TO_STOP:
            train->setPower(0);
            if (train->speed_in_kmh > this->maxSpeed - 5) {
                train->setBraking(2);
            } else if (train->speed_in_kmh > this->maxSpeed - 10) {
                train->setBraking(3);
            } else if (train->speed_in_kmh > 10) {
                train->setBraking(5);
            } else if (train->speed_in_kmh > 5){
                train->setBraking(2);
            } else if (train->speed_in_kmh > 2) {
                train->setBraking(1);
            }
            break;
        case Task::RECOVERY:
            if (train->speed_in_kmh == 0) {
                train->setBraking(0);
                this->decideTask();
            }
            break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(MS_DELAY));
}

void AI::decideTask() {
    if (train->emergency_braking) {
        currentTask = Task::RECOVERY;
    } else if (train->speed_in_kmh == 0) {
        currentTask = Task::ACCELERATE;
    } else if (train->speeding) {
        currentTask = Task::DECCELERATE_TO_LIMIT;
    } else {
        currentTask = Task::ACCELERATE;
    }
}

void AI::doTask() {

}

void AI::close() {
    running = false;
}