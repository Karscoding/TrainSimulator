//
// Created by Shadow on 10/9/2024.
//

#include "signal.h"

Signal::Signal(Simulator &sim, const char *image_path, Vector2 position, int aspect)
    : Object(sim, image_path, position), currentAspect(aspect) {}

Signal* Signal::createSignal(Simulator &sim, Vector2 position, int aspect) {
    const char *image_path;
    switch (aspect) {
        case LightAspects::RED:
            image_path = "../resources/Signals/LightSignals/RedTall.png";
            break;
        case LightAspects::GREEN:
            image_path = "../resources/Signals/LightSignals/GreenTall.png";
            break;
        case LightAspects::YELLOW:
            image_path = "../resources/Signals/LightSignals/YellowTall.png";
            break;
        case SignAspects::VMAX_40:
            image_path = "../resources/Signs/40Sign.png";
            break;
        case SignAspects::UPC_40:
            image_path = "../resources/Signs/40DownSign.png";
            break;
    }
    return new Signal(sim, image_path, position, aspect);
}
