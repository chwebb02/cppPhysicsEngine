#include "../include/collider.h"
#include "../include/geometry.h"
#include <math.h>

namespace physics {
bool collider::isColliding(collider& c1, collider &c2) {
    using geometry::vector;

    // Get the distance between the centers of both colliders
    double distBetween = (c1.transform - c2.transform).getMagnitude();

    // Get the distance to the nearest point to the other collider
    double d1 = c1.nearestTo(c2).getMagnitude();
    double d2 = c2.nearestTo(c1).getMagnitude();

    // If the distance between the points is greater than the distance
    // to the nearest points, then we do not have a collision
    if (distBetween > d1 + d2) {
        return false;
    }

    // Otherwise, the two colliders overlap and we return true
    return true;
}

geometry::vector collider::getTransform() {
    return transform;
}


// Begin Circle
geometry::vector circleCollider::nearestTo(collider &other) {
    using geometry::vector;

    vector toOther = other.getTransform() - transform;
    return toOther.scaled(radius) + transform;
}


// Begin Plane
geometry::vector planeCollider::nearestTo(collider& other) {
    using geometry::vector;

    vector pt = transform;

    // Run calculation to find point here
    vector toOther = other.getTransform() - transform;
    if (std::abs(vector::dotProduct(toOther, direction)) > TOLERANCE) {
        // Find the vector originating from other.getTransform()

    } else {
        return transform;
    }

    // Return pt if it is on the plane
    if (transform.x - length / 2 * direction.x <= pt.x && pt.x <= transform.x + length / 2 * direction.x) {
        if (transform.y - length / 2 * direction.y <= pt.y && pt.y <= transform.y + length / 2 * direction.y) {
            return pt;
        }
    }

    // Return the nearest endpoint if pt is not on the plane
    vector scaledDirection = direction.scaled(length);          // Get direction and magnitude
    vector endpoint1 = transform - scaledDirection;             // Calculate endpoint 1
    vector endpoint2 = transform + scaledDirection;             // Calculate endpoint 2

    // Get distance of pt to each endpoint
    double dist1 = (pt - endpoint1).getMagnitude();
    double dist2 = (pt - endpoint1).getMagnitude();

    // Return the endpoint that is closer to pt
    if (dist1 < dist2) {
        return endpoint1;
    }
    return endpoint2;
}
};