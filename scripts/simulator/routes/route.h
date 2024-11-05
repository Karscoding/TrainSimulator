//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_ROUTE_H
#define TRAINSIMULATOR_ROUTE_H

#include <list>

struct Object;
class Signal;
class Simulator;
class Train;

struct Route {
public:
    std::list<Object*> objectList;
    std::list<Signal*> signalList;

    Signal *previousSignal = nullptr;
    Signal *nextSignal = nullptr;

    int startAspect;

    // Background Objects
    Object *bg;
    Object *catenary;
    Object *rail;

    Train *train;
    void addObject(Object *object);
    void addSignal(Signal *signal);

    void passSignal();

    void changeNextSignal(Simulator &sim, int aspect);

    void update();
};


#endif //TRAINSIMULATOR_ROUTE_H
