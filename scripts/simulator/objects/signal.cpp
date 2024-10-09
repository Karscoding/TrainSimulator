//
// Created by Shadow on 10/9/2024.
//

#include "signal.h"

Signal::Signal(Simulator &sim, const char *image_path, Vector2 position, int aspect)
    : Object(sim, image_path, position), currentAspect(aspect) {}
