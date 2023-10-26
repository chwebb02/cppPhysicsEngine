#pragma once

#include "geometry.h"
#include <vector>

namespace physics {
class collider {
protected:
    geometry::vector transform;
public:
    const double TOLERANCE = 1e-9;
    geometry::vector getTransform();

    virtual geometry::vector nearestTo(collider& other);
    static bool isColliding(collider& c1, collider& c2);
};

class circleCollider: public collider {
private:
    double radius;                          // The radius of the circle
public:
    geometry::vector nearestTo(collider& other);
};

class planeCollider: public collider {
private:
    geometry::vector direction;             // The direction the plane is aligned to
    double length;                          // The length of the plane (half on either end of transform)
public:
    geometry::vector nearestTo(collider& other);
};

class generalCollider: public collider {
private:
    std::vector<geometry::vector> points;   // The points that define the shape (connected 0->1, 1->2, ..., (n-2)->(n-1), (n-1)->0)
public:

};
}