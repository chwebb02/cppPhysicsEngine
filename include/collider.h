#pragma once

#include "geometry.h"
#include <vector>

namespace physics {
const double COLLISION_TOLERANCE = 1e-15;

// Pure virtual class for all collider types
class collider {
protected:
    geometry::vector transform = geometry::vector(0, 0);
public:
    geometry::vector getTransform();

    // Get the points that define a collider
    virtual std::vector<geometry::vector> getPoints() = 0;

    // Get the nearest point on a colliders surface to a point
    virtual geometry::vector nearestPointToPoint(geometry::vector) = 0;

    // Get the nearest point on a colliders surface to another collider
    virtual geometry::vector nearestPointToCollider(collider& other);

    // Move or rotate the collider
    void translate(geometry::vector newPos);
    virtual void rotateBy(double radians) = 0;

    // Are two colliders colliding with one another
    static bool isColliding(collider& c1, collider& c2);
};

class circleCollider: public collider {
private:
    double radius;                          // The radius of the circle
public:
    circleCollider(geometry::vector transform, double radius);

    std::vector<geometry::vector> getPoints();

    geometry::vector nearestPointToPoint(geometry::vector point);
    geometry::vector nearestPointToCollider(collider& other);

    void rotateBy(double radians);
};

class lineCollider: public collider {
private:
    geometry::vector direction;
    double length;

public:
    lineCollider(geometry::vector transform, geometry::vector direction, double length);

    std::vector<geometry::vector> getPoints();

    geometry::vector nearestPointToPoint(geometry::vector point);

    void rotateBy(double radians);
};

class generalCollider: public collider {
private:
    std::vector<geometry::vector> points;   // The points that define the shape (connected 0->1, 1->2, ..., (n-2)->(n-1), (n-1)->0)

    int countEdgeCrosses(geometry::vector point);
public:
    generalCollider(geometry::vector transform, std::vector<geometry::vector> pts);

    std::vector<geometry::vector> getPoints();
    
    geometry::vector nearestPointToPoint(geometry::vector point);

    void rotateBy(double radians);
};
};