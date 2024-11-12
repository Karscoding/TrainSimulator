//
// Created by Shadow on 11/12/2024.
//

#include "placementScreen.h"
#include "structs/object.h"

PlacementScreen::PlacementScreen(Simulator &sim) {
    this->placementScreenBG = new Object(sim, "../resources/PlacementScreen.png", Vector2(0, -50));
    this->optionsScreenBG = new Object(sim, "../resources/OptionsScreen.png", Vector2(0, -50));
}