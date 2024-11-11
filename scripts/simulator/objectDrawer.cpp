//
// Created by Shadow on 9/25/2024.
//

#include "objectDrawer.h"
#include "simulator.h"
#include "structs/object.h"
#include "objects/station.h"
#include "structs/dimensions.h"

#define TILE_WIDTH 1920
#define BVL_WIDTH 1280
#define STATION_WIDTH 1280

void ObjectDrawer::draw(Object *object, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, object->sprite_texture, nullptr, &object->rect);
}

// This method looks complicated but is fairly simple, it basically makes sure the background moves based on the sim.screenPosition
// And that it moves the background based on a tile system to make sure the player doesn't the background is moved when off screen.
//
// TLDR: The moving background moves a tile forward when a player enters a new tile
void ObjectDrawer::drawTiledMovingBackground(SDL_Renderer *renderer, Simulator &sim) {

    // Draw background
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);
    sim.currentRoute->bg->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->bg->sprite_texture, nullptr, &sim.currentRoute->bg->rect);


    // Draw rails
    int screenSmallTilePosition = ceil(sim.screenPosition / BVL_WIDTH);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (BVL_WIDTH * (screenSmallTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (BVL_WIDTH * (screenSmallTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (BVL_WIDTH * (screenSmallTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);
    sim.currentRoute->catenary->rect.x = (int) -sim.screenPosition + (BVL_WIDTH * (screenSmallTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->catenary->sprite_texture, nullptr, &sim.currentRoute->catenary->rect);

    // Draw rails
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition - 1));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 0));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 1));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
    sim.currentRoute->rail->rect.x = (int) -sim.screenPosition + (TILE_WIDTH * (sim.screenTilePosition + 2));
    SDL_RenderCopy(renderer, sim.currentRoute->rail->sprite_texture, nullptr, &sim.currentRoute->rail->rect);
}

Dimensions ObjectDrawer::getImageDimensions(SDL_Texture *texture) {
    Dimensions size;
    SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
    return size;
}
