//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_TEXTDRAWER_H
#define TRAINSIMULATOR_TEXTDRAWER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "structs/vector2.h"
#include "structs/dimensions.h"

class TextDrawer {
public:
    static SDL_Texture* getTextTexture(const char* message, TTF_Font *font, SDL_Renderer& renderer);
    static void drawTextFromString(SDL_Renderer &renderer, std::string *message, TTF_Font *font, Vector2 position, SDL_Color color = SDL_Color(0, 0, 0, 0));
    static void draw(SDL_Texture *texture, SDL_Renderer& renderer, Vector2 position);
};


#endif //TRAINSIMULATOR_TEXTDRAWER_H
