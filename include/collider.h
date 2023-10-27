#pragma once

#include "geometry.h"
#include <vector>

namespace physics {
class collider {
protected:
    geometry::vector transform;
public:
    collider(geometry::vector transform);
    collider();
    geometry::vector getTransform();

    virtual geometry::vector nearestTo(collider& other) = 0;
    virtual std::vector<geometry::vector> getPoints() = 0;
    virtual geometry::vector getNormalPoint(geometry::vector point);

    static bool isColliding(collider& c1, collider& c2);
};

class circleCollider: public collider {
private:
    double radius;                          // The radius of the circle
public:
    circleCollider(geometry::vector transform, double radius);

    geometry::vector nearestTo(collider& other);
    std::vector<geometry::vector> getPoints();
    geometry::vector getNormalPoint(geometry::vector point);
};

class planeCollider: public collider {
private:
    geometry::vector direction;             // The unit direction the plane is aligned to
    double length;                          // The length of the plane (half on either end of transform)
public:
    planeCollider(geometry::vector transform, geometry::vector direction, double length);

    geometry::vector nearestTo(collider& other);
    std::vector<geometry::vector> getPoints();
    geometry::vector getNormalPoint(geometry::vector point);
};

class generalCollider: public collider {
private:
    std::vector<geometry::vector> points;   // The points that define the shape (connected 0->1, 1->2, ..., (n-2)->(n-1), (n-1)->0)
public:
    generalCollider(geometry::vector transform, std::vector<geometry::vector> pts);
    
    geometry::vector nearestTo(collider& other);
    std::vector<geometry::vector> getPoints();
    geometry::vector getNormalPoint(geometry::vector point);
};
}