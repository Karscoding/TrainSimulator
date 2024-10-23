//
// Created by Shadow on 9/25/2024.
//

#include "routeTest.h"
#include "../structs/object.h"
#include "../objects/train.h"
#include "../objects/signal.h"

RouteTest::RouteTest(Simulator &sim) {
    this->startAspect = SignAspects::VMAX_80;

    this->bg = new Object(sim, "../resources/Background.png", Vector2(0, 0));
    this->catenary = new Object(sim, "../resources/Bovenleiding.png", Vector2(0, 450));
    this->rail = new Object(sim, "../resources/Rails.png", Vector2(0, 848));
    this->train = new Train(sim, "../resources/VIRM.png", Vector2(-500, 650), 2, 3, 0.02);

    auto *signal = Signal::createSignal(sim, 500, LightAspects::GREEN);
    this->addObject(signal);
    this->addSignal(signal);

    auto *sign = Signal::createSignal(sim, 700, SignAspects::VMAX_40);
    this->addObject(sign);
    this->addSignal(sign);

    auto *sign_130 = Signal::createSignal(sim, 8000, SignAspects::VMAX_130);
    this->addObject(sign_130);
    this->addSignal(sign_130);

    auto *yellow_signal = Signal::createSignal(sim, 16000, LightAspects::YELLOW);
    this->addObject(yellow_signal);
    this->addSignal(yellow_signal);
}
