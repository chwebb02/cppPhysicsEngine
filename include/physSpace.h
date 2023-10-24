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

    void AddPhysObj(physObj *obj);
    void RemoveObj(physObj *obj);

    void update(double delta);
};
};