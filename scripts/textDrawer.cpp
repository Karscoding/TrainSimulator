//
// Created by Shadow on 9/25/2024.
//

#include "textDrawer.h"

SDL_Texture* TextDrawer::getTextTexture(const char *message, TTF_Font *font, SDL_Renderer &renderer) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font,message, { 0xFF, 0xFF, 0xFF, 0 });
    return SDL_CreateTextureFromSurface(&renderer, surface);
}

void TextDrawer::draw(SDL_Texture *texture, SDL_Renderer &renderer, Vector2 position) {
    Dimensions size;
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    SDL_RenderCopy(&renderer, texture, NULL, new SDL_Rect(position.x, position.y, size.width, size.height));
}