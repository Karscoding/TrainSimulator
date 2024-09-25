//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_OBJECTDRAWER_H
#define TRAINSIMULATOR_OBJECTDRAWER_H

#include <SDL.h>
#include <SDL_image.h>

#include "structs/object.h"

struct Object;

class ObjectDrawer {
public:
    static void draw(Object *object, SDL_Renderer *renderer);
    static Dimensions getImageDimensions(SDL_Texture *texture);
};


#endif //TRAINSIMULATOR_OBJECTDRAWER_H
