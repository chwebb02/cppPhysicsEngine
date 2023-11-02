#pragma once

#include "geometry.h"
#include "collider.h"

namespace physics {
class physObj {
protected:
    geometry::vector position;
    collider& coll;
public:
};

class dynamicObj : public physObj {
private:
    geometry::vector velocity;
    geometry::vector acceleration;
    double mass;

    // Other properties
    double elasticity;          // 0 - 1: 0 = complete absorption, 1 = complete energy conservation

public:
    void handleCollision(physObj& other);
    void handleCollision(dynamicObj& other);

    geometry::vector getVelocity();
    geometry::vector getAcceleration();

    void setVelocity(geometry::vector newVelocity);
    void setAcceleration(geometry::vector newAccel);
};
};