//
// Created by Shadow on 11/11/2024.
//

#ifndef TRAINSIMULATOR_STATION_H
#define TRAINSIMULATOR_STATION_H

#include "../structs/object.h"

class Station : public Object {
public:
    int tileSpan;
    int stoppingPosition;
    int beginPosition;
    Station(Simulator &sim, int xPosition, int tileSpan);
};


#endif //TRAINSIMULATOR_STATION_H
