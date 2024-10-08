//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_OBJECTDRAWER_H
#define TRAINSIMULATOR_OBJECTDRAWER_H

#include <SDL.h>
#include "simulator.h"

struct Object;
struct Dimensions;

class ObjectDrawer {
public:
    static void draw(Object *object, SDL_Renderer *renderer);
    static Dimensions getImageDimensions(SDL_Texture *texture);
    static void drawTiledMovingBackground(SDL_Renderer *renderer, Simulator &sim);
};


#endif //TRAINSIMULATOR_OBJECTDRAWER_H
