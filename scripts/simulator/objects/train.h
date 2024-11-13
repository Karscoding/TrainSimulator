//
// Created by Shadow on 9/26/2024.
//

#ifndef TRAINSIMULATOR_TRAIN_H
#define TRAINSIMULATOR_TRAIN_H

#include "../structs/object.h"

class Train : public Object {
private:
    void applyPower(float value);
    void applyBraking(float value);
public:
    float speed = 0;
    float speed_in_kmh = 0;

    float braking_power;
    float traction_power;
    float resistance;

    Signal *previousSignal = nullptr;
    Signal *nextSignal = nullptr;
    float distance_next_signal = 0;

    Station *nextStation = nullptr;
    float distance_next_station = 10000;
    float distance_next_station_end = 10000;

    int train_pos_offset;

    bool applying_power = false;
    bool applying_braking = false;

    bool doors_opened = false;

    bool atStation = false;
    bool stationComplete = false;

    bool emergency_braking = false;
    bool speeding = false;
    int speeding_timer = 0;
    int speeding_threshold = 300;

    int traction_setting = 0;
    int braking_setting = 0;

    float kwh_used = 0;

    int current_vmax = 0;

    int segment_vmax = 40;

    Train(Simulator &sim, const char *image_path, Vector2 position, float braking_power, float traction_power, float resistance);

    void increasePower();
    void setPower(int value);
    void increaseBraking();
    void setBraking(int value);
    void decreasePower();
    void decreaseBraking();

    void resetPowerAndBraking();

    void openDoors();
    void closeDoors();

    void applyEmergencyBraking();

    void roll();

    void update(Simulator &sim);
};


#endif //TRAINSIMULATOR_TRAIN_H
