//
// Created by Shadow on 9/25/2024.
//

#include "routeTest.h"
#include "../structs/object.h"
#include "../objects/train.h"
#include "../objects/signal.h"

RouteTest::RouteTest(Simulator &sim) {
    this->bg = new Object(sim, "../resources/Background.png", Vector2(0, 0));
    this->catenary = new Object(sim, "../resources/Bovenleiding.png", Vector2(0, 450));
    this->rail = new Object(sim, "../resources/Rails.png", Vector2(0, 848));
    this->train = new Train(sim, "../resources/VIRM.png", Vector2(-500, 650), 2, 3, 0.02);

    this->addObject(new Signal(sim, "../resources/Signals/LightSignals/GreenTall.png", Vector2(200, 300), LightAspects::GREEN));
}
