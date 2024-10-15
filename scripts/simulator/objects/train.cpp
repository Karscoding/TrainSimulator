//
// Created by Shadow on 9/26/2024.
//

#include "train.h"
#include "signal.h"

// Private
void Train::applyPower(float value) {
    this->applying_power = true;
    if (this->speed == 0) {
        this->speed += (value * this->traction_power) / 60;
        this->kwh_used += (20 / 10000) * this->traction_setting;
    } else if (this->speed < 15) {
        this->speed += (value * this->traction_power / 7) / 60;
        this->kwh_used += (10 / 10000) * this->traction_setting;
    } else {
        this->speed += ((value * this->traction_power) / this->speed) / 60;
        this->kwh_used += (5 / 10000) * this->traction_setting;
    }
}

void Train::applyBraking(float value) {
    this->applying_braking = true;
    if (this->speed == 0 || this->speed < 0 || 0.1 > this->speed > 0) {
        this->speed = 0;
    } else if (this->speed <= 15) {
        this->speed -= (value * this->braking_power / 3) / 60;
    } else {
        this->speed -= ((value * this->braking_power) / (this->speed / 5)) / 60;
    }
}


// Public
Train::Train(Simulator &sim, const char *image_path, Vector2 position, float braking_power, float traction_power, float resistance)
    : Object(sim, image_path, position), braking_power(braking_power), traction_power(traction_power), resistance(resistance) {
    this->train_pos_offset = this->dimensions.width;
}

void Train::increasePower() {
    if ((this->traction_setting <= 6 && this->braking_setting == 0) && !doors_opened) {
        this->traction_setting++;
    }
}

void Train::setPower(int value) {
    if (value <= 7 && value >= 0) {
        this->traction_setting = value;
    }
}

void Train::increaseBraking() {
    if (this->braking_setting <= 6 && this->traction_setting == 0) {
        this->braking_setting++;
    }
}

void Train::setBraking(int value) {
    if (value <= 7 && value >= 0) {
        this->braking_setting = value;
    }
}

void Train::decreasePower() {
    if (this->traction_setting > 0) {
        this->traction_setting--;
    }
}

void Train::decreaseBraking() {
    if (0 < this->braking_setting && this->braking_setting <= 7) {
        this->braking_setting--;
    } else if (this->emergency_braking && this->speed == 0) {
        this->braking_setting--;
        this->emergency_braking = false;
    }
}

void Train::resetPowerAndBraking() {
    if (!this->emergency_braking) {
        this->applying_braking = false;
        this->applying_power = false;
        this->braking_setting = 0;
        this->traction_setting = 0;
    }
}

void Train::openDoors() {
    if (this->speed == 0) {
        this->doors_opened = true;
    }
}

void Train::closeDoors() {
    this->doors_opened = false;
}

void Train::applyEmergencyBraking() {
    this->resetPowerAndBraking();
    this->braking_setting = 8;
    this->emergency_braking = true;
}


void Train::roll() {
    this->applying_braking = false;
    this->applying_power = false;
    if (this->speed > 0.5) {
        this->speed -= this->resistance / 60;
    } else {
        this->speed = 0;
    }

    this->kwh_used += 5 / 1000000;
}


void Train::update(Simulator &sim) {
    this->nextSignal = sim.currentRoute->nextSignal;
    if (this->nextSignal->position.x < (int) sim.screenPosition + 400) {
        sim.currentRoute->passSignal();
    }

    if (this->speed_in_kmh > (float) sim.currentRoute->nextSignal->currentAspect + 5) {
        this->speeding = true;
    } else {
        this->speeding = false;
    }

    if (this->speeding) {
        this->speeding_timer++;
        if (this->speeding_timer > this->speeding_threshold) {
            this->applyEmergencyBraking();
        }
    } else {
        this->speeding_timer = 0;
    }

    if (this->traction_setting > 0) {
        this->applyPower((float) this->traction_setting / 10);
    } else if (this->braking_setting > 0) {
        this->applyBraking((float) this->braking_setting / 4);
    } else {
        this->roll();
    }

    if (this->speed != 0) {
        this->speed_in_kmh = this->speed * 6.5f;
    } else {
        this->speed_in_kmh = 0;
    }
}