#pragma once

#include "geometry.h"
#include "collider.h"

namespace physics {
// There may be a need for tolerances

class physObj {
protected:
    geometry::vector position;
    collider& coll;
public:
};

class dynamicObj : public physObj {
private:
    geometry::vector velocity;
    geometry::vector force;
    double mass;

    // Other properties
    double elasticity;          // 0 - 1: 0 = complete absorption, 1 = complete energy conservation

public:
    void step(double delta);

    static void collide(dynamicObj& o1, dynamicObj& o2);
};
};