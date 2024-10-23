//
// Created by Shadow on 10/9/2024.
//

#include "signal.h"

Signal::Signal(Simulator &sim, const char *image_path, Vector2 position, int aspect)
    : Object(sim, image_path, position), currentAspect(aspect) {}

Signal* Signal::createSignal(Simulator &sim, int xPosition, int aspect) {
    const char *image_path;
    int yPosition = 0;
    switch (aspect) {
        case LightAspects::RED:
            image_path = "../resources/Signals/LightSignals/RedTall.png";
            yPosition = 300;
            break;
        case LightAspects::GREEN:
            image_path = "../resources/Signals/LightSignals/GreenTall.png";
            yPosition = 300;
            break;
        case LightAspects::YELLOW:
            image_path = "../resources/Signals/LightSignals/YellowTall.png";
            yPosition = 300;
            break;
        case SignAspects::VMAX_130:
            image_path = "../resources/Signals/Signs/130UpSign.png";
            yPosition = 600;
            break;
        case SignAspects::VMAX_40:
            image_path = "../resources/Signals/Signs/40Sign.png";
            yPosition = 600;
            break;
        case SignAspects::UPC_40:
            image_path = "../resources/Signals/Signs/40DownSign.png";
            yPosition = 600;
            break;
    }
    return new Signal(sim, image_path, Vector2(xPosition, yPosition), aspect);
}
