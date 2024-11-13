//
// Created by Shadow on 11/11/2024.
//

#include "station.h"

Station::Station(Simulator &sim, int xPosition, int tileSpan)
    : Object(sim, "../resources/Station2.png", Vector2(xPosition, 340)), tileSpan(tileSpan) {
    stoppingPosition = (xPosition + (tileSpan * 1280)) - 900;
    beginPosition = xPosition;
}