//
// Created by Shadow on 9/26/2024.
//

#include "train.h"
#include "signal.h"
#include "station.h"

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
    if (this->applying_braking) { this->traction_setting = 0; }
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
    if (this->emergency_braking) {
        if (this->speed_in_kmh != 0) {
            return;
        }
    }
    if (this->applying_power) { this->braking_setting = 0; }
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
        this->traction_setting = 0;
        this->braking_setting = 0;
        this->applying_braking = false;
        this->applying_power = false;
    }
}

void Train::openDoors() {
    if (this->speed == 0) {
        this->doors_opened = true;
    }
}

void Train::closeDoors() {
    this->doors_opened = false;
    this->stationComplete = true;
}

void Train::applyEmergencyBraking() {
    this->resetPowerAndBraking();
    this->braking_setting = 8;
    this->emergency_braking = true;
}

// Applying resistance
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
    if (sim.currentRoute->previousSignal != nullptr) {
        this->previousSignal = sim.currentRoute->previousSignal;
        if (this->segment_vmax > this->previousSignal->currentAspect || this->current_vmax == 0) {
            this->current_vmax = this->previousSignal->currentAspect;
        }

        // This is true when the signal is a Sign which shows the vmax of a segment
        if (this->previousSignal->currentAspect % 10 == 0) {
            this->segment_vmax = this->previousSignal->currentAspect;
        }

        if (this->nextSignal->currentAspect == LightAspects::GREEN) {
            this->current_vmax = this->segment_vmax;
        } else if (this->previousSignal->currentAspect == LightAspects::YELLOW) {
            this->current_vmax = 40;
        } else if (this->previousSignal->currentAspect == LightAspects::GREEN) {
            this->current_vmax = segment_vmax;
        }

        // Speeding checks
        if (this->speed_in_kmh > (float) sim.currentRoute->previousSignal->currentAspect + 5 && !this->applying_braking) {
            this->speeding = true;
        } else {
            this->speeding = false;
        }

    } else if (sim.currentRoute->nextSignal != nullptr) {
        this->current_vmax = sim.currentRoute->startAspect;
        this->nextSignal = sim.currentRoute->nextSignal;
    } else {
        this->current_vmax = sim.currentRoute->startAspect;
        this->segment_vmax = sim.currentRoute->startAspect;
        return;
    }

    this->nextSignal = sim.currentRoute->nextSignal;

    this->distance_next_signal = (float) sim.currentRoute->nextSignal->position.x - sim.screenPosition;

    // Reset emergency_braking boolean
    if (this->emergency_braking && this->speed_in_kmh == 0 && this->braking_setting == 0) {
        this->emergency_braking = false;
    }

    // Pass signal
    if (this->nextSignal->position.x < (int) sim.screenPosition + 400) {
        if (this->nextSignal->currentAspect == 0) {
            this->applyEmergencyBraking();
        }
        sim.currentRoute->passSignal();
    }

    if (this->nextSignal->currentAspect == LightAspects::RED && this->speed_in_kmh == 0) {
        sim.currentRoute->changeNextSignal(sim, LightAspects::GREEN);
    }

    if (stationComplete) {
        sim.currentRoute->passStation();
        atStation = false;
        stationComplete = false;
    }

    if (sim.currentRoute->nextStation != nullptr) {
        this->nextStation = sim.currentRoute->nextStation;
        distance_next_station = (float) this->nextStation->beginPosition - sim.screenPosition;
        distance_next_station_end = (float) this->nextStation->stoppingPosition - sim.screenPosition;

        if (distance_next_station < 0 && distance_next_station_end > 0) {
            atStation = true;
        } else if (distance_next_station_end < 0) {
            atStation = false;
            sim.currentRoute->passStation();
        } else {
            atStation = false;
        }
    } else {
        distance_next_station_end = 100000;
    }



    // Timer for emergency brake upon speeding
    if (this->speeding) {
        this->speeding_timer++;
        if (this->speeding_timer > this->speeding_threshold) {
            this->applyEmergencyBraking();
        }
    } else {
        this->speeding_timer = 0;
    }

    // Applying forces
    if (this->traction_setting > 0) {
        this->applyPower((float) this->traction_setting / 10);
    } else {
        this->applying_power = false;
    }

    if (this->braking_setting > 0) {
            this->applyBraking((float) this->braking_setting / 4);
    } else {
        this->applying_braking = false;
    }

    if (this->braking_setting == 0 && this->traction_setting == 0) {
        this->roll();
    }

    // Speed to km/h conversion
    if (this->speed != 0) {
        this->speed_in_kmh = this->speed * 6.5f;
    } else {
        this->speed_in_kmh = 0;
    }
}