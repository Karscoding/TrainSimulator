//
// Created by Shadow on 9/25/2024.
//



#ifndef TRAINSIMULATOR_OBJECT_H
#define TRAINSIMULATOR_OBJECT_H

#include "vector2.h"
#include "dimensions.h"
#include "../objectDrawer.h"
#include "../simulator.h"
#include <SDL.h>
#include <SDL_image.h>

class Simulator;

struct Object {
public:
    SDL_Rect rect;

    SDL_Texture *sprite_texture;

    Vector2 position;
    Dimensions dimensions;

    Object(Simulator &sim, const char *image_path, Vector2 position);
    Object(Simulator &sim, const char *image_path, Vector2 position, Dimensions dimensions);
};


#endif //TRAINSIMULATOR_OBJECT_H
