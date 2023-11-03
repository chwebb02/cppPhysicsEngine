#pragma once

#include "geometry.h"
#include <vector>

namespace physics {
class collider {
protected:
    geometry::vector transform = geometry::vector(0, 0);
public:
    geometry::vector getTransform();

    virtual std::vector<geometry::vector> getPoints() = 0;

    virtual geometry::vector nearestPointToPoint(geometry::vector) = 0;
    geometry::vector nearestPointToCollider(collider& other);

    void translate(geometry::vector newPos);
    virtual void rotateBy(double radians) = 0;

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