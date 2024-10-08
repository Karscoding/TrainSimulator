//
// Created by Shadow on 9/25/2024.
//

#include "textDrawer.h"

SDL_Texture* TextDrawer::getTextTexture(const char *message, TTF_Font *font, SDL_Renderer &renderer) {
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font,message, { 0xFF, 0xFF, 0xFF, 0 });
    return SDL_CreateTextureFromSurface(&renderer, surface);
}


// TODO: Add SDL_Color parameter with default value of Black
void TextDrawer::drawTextFromString(SDL_Renderer &renderer, std::string *message, TTF_Font *font, Vector2 position, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, message->c_str(), color);
    Dimensions size;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    SDL_RenderCopy(&renderer, texture, NULL, new SDL_Rect(position.x, position.y, size.width, size.height));
}

void TextDrawer::draw(SDL_Texture *texture, SDL_Renderer &renderer, Vector2 position) {
    Dimensions size;
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    SDL_RenderCopy(&renderer, texture, NULL, new SDL_Rect(position.x, position.y, size.width, size.height));
}
