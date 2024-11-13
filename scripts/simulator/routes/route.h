//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_ROUTE_H
#define TRAINSIMULATOR_ROUTE_H

#include <list>

struct Object;
class Signal;
class Station;
class Simulator;
class Train;
class PlacementScreen;

struct Route {
public:
    std::list<Object*> objectList;
    std::list<Signal*> signalList;
    std::list<Station*> stationList;

    Signal *previousSignal = nullptr;
    Signal *nextSignal = nullptr;

    Station *nextStation = nullptr;

    int startAspect;

    // Background Objects
    Object *bg;
    Object *catenary;
    Object *rail;

    Train *train;
    void addObject(Object *object);
    void addSignal(Signal *signal);
    void addStation(Simulator &sim, Station *station);

    static Route* createRouteBasedOnTiles(Simulator &sim, PlacementScreen *placementScreen);

    void passSignal();
    void passStation();

    void changeNextSignal(Simulator &sim, int aspect);

    void update();
};


#endif //TRAINSIMULATOR_ROUTE_H
