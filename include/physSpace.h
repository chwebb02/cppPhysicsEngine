#pragma once

#include <vector>
#include "physObj.h"
#include "geometry.h"

namespace physics {
class physSpace {
private:
    std::vector<physObj *> physObjs;
    geometry::vector gravity;

    physSpace(geometry::vector gravity);
public:
    class builder {
    private:
        geometry::vector gravity;
    public:
        builder addGravity(geometry::vector gravity);
        physSpace build();  
    };

    void AddPhysObj(physObj *obj);		// Add an object to the physicsSpace
    void RemoveObj(physObj *obj);		// Remove an existing object from the physicsSpace

    void update(double delta);			// Process a singular step, dependent on the time since last step
};
};
