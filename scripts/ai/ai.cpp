#include "ai.h"
#include <chrono>
#include <thread>

#define MS_DELAY 100
#define STOP_TIME 5

AI::AI(Train *train, float maxSpeed)
    : train(train), maxSpeed(maxSpeed) {}

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
            } else if (train->speed_in_kmh > this->maxSpeed + 5) {
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
            brakeFactor = train->speed_in_kmh * (train->distance_next_signal / 1000);
            if (brakeFactor > 300) {
                train->applyEmergencyBraking();
            } else if (brakeFactor > 250) {
                train->setBraking(7);
            } else if (brakeFactor > 200) {
                train->setBraking(6);
            } else if (brakeFactor > 150) {
                train->setBraking(5);
            } else if (brakeFactor > 100) {
                train->setBraking(5);
            } else {
                if (train->speed_in_kmh < 20 && train->distance_next_signal > 2000) {
                    train->setBraking(0);
                } else if (train->speed_in_kmh > 0 && train->distance_next_signal < 1000) {
                    train->setBraking(3);
                } else {
                    train->setBraking(2);
                }
            }
            break;
        case Task::RECOVERY:
            if (train->speed_in_kmh == 0) {
                train->setBraking(0);
                this->decideTask();
            }
            break;
        case Task::PASSENGER_STOP:
            train->openDoors();
            std::this_thread::sleep_for(std::chrono::seconds(STOP_TIME));
            train->closeDoors();
    }

    this->decideTask();

    std::this_thread::sleep_for(std::chrono::milliseconds(MS_DELAY));
}

void AI::decideTask() {
    if (train->atStation) {
        if (currentTask == Task::PASSENGER_STOP) {
            currentTask = Task::ACCELERATE;
        } else if (train->speed_in_kmh > 0) {
            currentTask = Task::DECCELERATE_TO_STOP;
        } else {
            currentTask = Task::PASSENGER_STOP;
        }
    } else if (train->nextSignal != nullptr) {
        if (train->previousSignal != nullptr) {
            this->maxSpeed = (float) train->previousSignal->currentAspect;
        }
        auto nextLimit = train->nextSignal->currentAspect;
        if (currentTask == Task::DECCELERATE_TO_STOP && train->nextSignal->currentAspect != LightAspects::RED) {
            currentTask = Task::ACCELERATE;
        } else if (nextLimit == LightAspects::RED) {
            this->maxSpeed = 0;
            currentTask = Task::DECCELERATE_TO_STOP;
        } else if (train->speed_in_kmh > (float) nextLimit + 5 && train->distance_next_signal < (train->speed_in_kmh - (float) nextLimit) * 150) {
            this->maxSpeed = (float) nextLimit;
            currentTask = Task::DECCELERATE_TO_LIMIT;
        } else if (train->speed_in_kmh < this->maxSpeed - 10) {
            currentTask = Task::ACCELERATE;
        } else if (train->speed_in_kmh == 0) {
            currentTask = Task::WAITING;
        } else {
            currentTask = Task::COASTING;
        }
    } else {
        if (train->emergency_braking) {
            currentTask = Task::RECOVERY;
        } else if (train->speed_in_kmh == 0 && !train->doors_opened) {
            currentTask = Task::ACCELERATE;
        } else if (train->speed_in_kmh > this->maxSpeed + 5 || train->speeding) {
            currentTask = Task::DECCELERATE_TO_LIMIT;
        } else {
            currentTask = Task::ACCELERATE;
        }
    }
}

void AI::doTask() {

}

void AI::close() {
    running = false;
}