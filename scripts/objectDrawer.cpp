//
// Created by Shadow on 9/25/2024.
//

#include "objectDrawer.h"

void ObjectDrawer::draw(Object *object, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, object->sprite_texture, nullptr, &object->rect);
}

Dimensions ObjectDrawer::getImageDimensions(SDL_Texture *texture) {
    Dimensions size;
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    return size;
}
