//
// Created by Shadow on 9/25/2024.
//

#include "object.h"

Object::Object(Simulator &sim, const char *image_path, Vector2 position, Dimensions dimensions)
    : position(position), dimensions(dimensions) {
    this->rect = SDL_Rect(position.x, position.y, dimensions.width, dimensions.height);
    this->sprite_texture = IMG_LoadTexture(sim.renderer, image_path);
}