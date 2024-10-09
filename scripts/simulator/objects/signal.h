//
// Created by Shadow on 10/9/2024.
//

#ifndef TRAINSIMULATOR_SIGNAL_H
#define TRAINSIMULATOR_SIGNAL_H

#include "../structs/object.h"

enum LightAspects {
    RED,
    GREEN,
    GREEN_80,
    GREEN_FLASHING,
    YELLOW,
    YELLOW_60,
    YELLOW_80,
    YELLOW_130,
};

enum SignAspects {
    VMAX_40,
    VMAX_80,
    VMAX_140,
    UPC_40,
    UPC_80,
};

class Signal : public Object {
public:
    bool broken = false;
    int currentAspect;

    Signal(Simulator &sim, const char *image_path, Vector2 position, int aspect);
};


#endif //TRAINSIMULATOR_SIGNAL_H
