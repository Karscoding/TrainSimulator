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
    Train *train;
    void addObject(Object *object);
};


#endif //TRAINSIMULATOR_ROUTE_H
