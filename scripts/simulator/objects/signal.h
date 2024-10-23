//
// Created by Shadow on 10/9/2024.
//

#ifndef TRAINSIMULATOR_SIGNAL_H
#define TRAINSIMULATOR_SIGNAL_H

#include "../structs/object.h"

// Speed limites encoding:
// Only the first number matters, the second number has other meaning
// Example: 142 means 140 speed limit with 2 meaning it's a light signal
// 1 Means it's an upcoming limit at the next signal
// 3 Means it's an upcoming limit shown at yellow signal
enum LightAspects {
    RED = 0,
    GREEN = 142,
    GREEN_80 = 82,
    GREEN_FLASHING = 42,
    YELLOW = 43,
    YELLOW_60 = 63,
    YELLOW_80 = 83,
    YELLOW_130 = 133,
};

enum SignAspects {
    VMAX_40 = 40,
    VMAX_80 = 80,
    VMAX_130 = 130,
    VMAX_140 = 140,
    UPC_40 = 41,
    UPC_80 = 81,
};

class Signal : public Object {
private:
    Signal(Simulator &sim, const char *image_path, Vector2 position, int aspect);
public:
    bool broken = false;

    int currentAspect;
    static Signal* createSignal(Simulator &sim, int xPosition, int aspect);
};


#endif //TRAINSIMULATOR_SIGNAL_H
