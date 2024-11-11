//
// Created by Shadow on 9/25/2024.
//

#include "routeTest.h"
#include "../structs/object.h"
#include "../objects/train.h"
#include "../objects/station.h"
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

    auto *station = new Station(sim, -300, 1);
    this->addStation(station);

    auto *yellow_signal = Signal::createSignal(sim, 4500, LightAspects::YELLOW);
    this->addObject(yellow_signal);
    this->addSignal(yellow_signal);

    auto *red_signal = Signal::createSignal(sim, 8500, LightAspects::RED);
    this->addObject(red_signal);
    this->addSignal(red_signal);

    auto *sign_130 = Signal::createSignal(sim, 10000, SignAspects::VMAX_130);
    this->addObject(sign_130);
    this->addSignal(sign_130);

    auto *green_signal = Signal::createSignal(sim, 14500, LightAspects::GREEN);
    this->addObject(green_signal);
    this->addSignal(green_signal);

    auto *green_signal2 = Signal::createSignal(sim, 18500, LightAspects::GREEN);
    this->addObject(green_signal2);
    this->addSignal(green_signal2);

    auto *green_signal3 = Signal::createSignal(sim, 22500, LightAspects::GREEN);
    this->addObject(green_signal3);
    this->addSignal(green_signal3);

    auto *red_signal_oops = Signal::createSignal(sim, 26500, LightAspects::RED);
    this->addObject(red_signal_oops);
    this->addSignal(red_signal_oops);
}
