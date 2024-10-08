//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_ROUTE_H
#define TRAINSIMULATOR_ROUTE_H

#include <list>

struct Object;
class Train;

struct Route {
public:
    std::list<Object*> objectList;

    // Background Objects
    Object *bg;
    Object *catenary;
    Object *rail;

    Train *train;
    void addObject(Object *object);
    void update();
};


#endif //TRAINSIMULATOR_ROUTE_H
