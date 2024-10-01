//
// Created by Shadow on 9/25/2024.
//



#ifndef TRAINSIMULATOR_OBJECT_H
#define TRAINSIMULATOR_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>

#include "../simulator.h"
#include "vector2.h"
#include "../structs/dimensions.h"


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
