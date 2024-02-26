#pragma once

#include <vector>
#include "physObj.h"
#include "geometry.h"

namespace physics {
class physSpace {
private:
    std::vector<physObj *> physObjs;
    geometry::vector gravity;

public:
    physSpace(geometry::vector gravity);    // Create an empty physicsSpace

    void AddPhysObj(physObj *obj);		    // Add an object to the physicsSpace
    void RemoveObj(physObj *obj);		    // Remove an existing object from the physicsSpace

    void update(double delta);			    // Process a singular step, dependent on the time since last step
};
};
