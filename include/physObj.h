#pragma once

#include "geometry.h"
#include "collider.h"

namespace physics {
class physObj {
protected:
    geometry::vector position;
    collider coll;
public:

};

class dynamicObj : public physObj {
private:
    geometry::vector velocity;
    geometry::vector acceleration;
    double mass;

    // Other properties
    double elasticity;

public:
    
};
};