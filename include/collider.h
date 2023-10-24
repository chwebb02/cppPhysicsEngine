#pragma once

#include "geometry.h"
#include <vector>

namespace physics {
class collider {
protected:
    geometry::vector transform;
public:

};

class circleCollider : public collider {
private:
    double radius;                          // The radius of the circle
public:
};

class planeCollider: public collider {
private:
    geometry::vector direction;             // The direction the plane is aligned to
    double length;                          // The length of the plane (half on either end of transform)
public:

};

class generalCollider : public collider {
private:
    std::vector<geometry::vector> points;   // The points that define the shape (connected 0->1, 1->2, ..., (n-2)->(n-1), (n-1)->0)
public:

};
}