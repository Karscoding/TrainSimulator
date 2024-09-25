//
// Created by Shadow on 9/25/2024.
//

#ifndef TRAINSIMULATOR_ROUTE_H
#define TRAINSIMULATOR_ROUTE_H

#include <list>
#include "../structs/object.h"

struct Object;

struct Route {
public:
    std::list<Object*> objectList;
    void addObject(Object *object);
};


#endif //TRAINSIMULATOR_ROUTE_H
