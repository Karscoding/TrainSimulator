//
// Created by Shadow on 9/25/2024.
//

#include "objectDrawer.h"
#include "simulator.h"
#include "structs/object.h"
#include "structs/dimensions.h"

void ObjectDrawer::draw(Object *object, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, object->sprite_texture, nullptr, &object->rect);
}

void ObjectDrawer::drawTiledMovingBackground(SDL_Renderer *renderer, Simulator &sim) {
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);


    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);


    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (sim.SCREEN_WIDTH * (sim.screenTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
}

Dimensions ObjectDrawer::getImageDimensions(SDL_Texture *texture) {
    Dimensions size;
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    return size;
}
