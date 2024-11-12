//
// Created by Shadow on 11/12/2024.
//

#ifndef TRAINSIMULATOR_PLACEMENTSCREEN_H
#define TRAINSIMULATOR_PLACEMENTSCREEN_H

#include <map>

struct Station;
struct Object;
struct Signal;
class Simulator;

class PlacementScreen {
public:
    std::map<int, Signal*> lightSignalTiles;
    std::map<int, Signal*> signSignalTiles;
    std::map<int, Station*> stationTiles;

    Object *placementScreenBG;
    Object *optionsScreenBG;

    int selected = -1;

    PlacementScreen(Simulator &sim);
};


#endif //TRAINSIMULATOR_PLACEMENTSCREEN_H
