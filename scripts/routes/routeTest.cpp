//
// Created by Shadow on 9/25/2024.
//

#include "routeTest.h"
#include "../structs/object.h"
#include "../objects/train.h"

RouteTest::RouteTest(Simulator &sim) {
    this->bg = new Object(sim, "../resources/Background.png", Vector2(0, 0));
    this->catenary = new Object(sim, "../resources/Bovenleiding.png", Vector2(0, 180));
    this->rail = new Object(sim, "../resources/Rails.png", Vector2(0, 578));
    this->train = new Train(sim, "../resources/VIRM.png", Vector2(-500, 380), 2, 3, 0.02);
}
