//
// Created by Shadow on 9/25/2024.
//

#include "routeTest.h"

RouteTest::RouteTest(Simulator &sim) {
    this->addObject(new Object(sim, "../resources/Background.png", Vector2(0, 0)));
    this->addObject(new Object(sim, "../resources/Bovenleiding.png", Vector2(0, 180)));
    this->addObject(new Object(sim, "../resources/VIRM.png", Vector2(-500, 380), Dimensions(1000, 200)));
    this->addObject(new Object(sim, "../resources/Rails.png", Vector2(0, 578)));
}
