#include "../include/collider.h"
#include "../include/geometry.h"
#include <math.h>
#include <vector>
#include <iostream>

namespace physics {
collider::collider() : transform(0, 0) {
    
}

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

geometry::vector collider::nearestTo(collider& other) {
    using geometry::vector;

    vector out = transform;
    std::vector<vector> otherPoints = other.getPoints();

    // Find the nearest point on the line to each point on the otherCollider
    int numOtherPoints = otherPoints.size();
    double distance = MAXFLOAT;
    for (int i = 0; i < numOtherPoints; i++) {
        // Intuition explained in getNormalTo()
        vector candidatePoint = getNormalPoint(otherPoints[i]);

        // Get the distance between candidate point and the current point
        double currentDist = (candidatePoint - otherPoints[i]).getMagnitude();

        // If the distance is less than the current least, set the least to current
        if (currentDist < distance) {
            distance = currentDist;
            out = candidatePoint;
        }
    }

    return out;
}


// Begin Circle
circleCollider::circleCollider(geometry::vector transform, double radius) {
    this->transform = transform;
    this->radius = radius;
}


geometry::vector circleCollider::nearestTo(collider &other) {
    using geometry::vector;

    // Get the point on the other surface that we will collide
    // Then get a direction vector to that point
    vector otherNormalPt = other.getNormalPoint(transform);
    vector toPoint = otherNormalPt - transform;

    // Return the point on this surface closest to the other surface collision point
    return transform + otherNormalPt.absoluteScaled(radius);
}

std::vector<geometry::vector> circleCollider::getPoints() {
    std::vector<geometry::vector> out;
    out.push_back(transform);
    return out;
}

geometry::vector circleCollider::getNormalPoint(geometry::vector point) {
    using geometry::vector;

    vector toPoint = point - transform;
    return transform + toPoint.scaled(radius);
}


// Begin Plane
planeCollider::planeCollider(geometry::vector transform, geometry::vector direction, double length) : direction(0, 0) {
    this->transform = transform;
    this->direction = direction.normalized();
    this->length = length;
}

geometry::vector vectorAverage(const geometry::vector& v1, const geometry::vector& v2) {
    return geometry::vector((v1.x + v2.x) / 2, (v1.y + v2.y) / 2);
}

std::vector<geometry::vector> planeCollider::getPoints() {
    std::vector<geometry::vector> out;
    out.push_back(transform);
    out.push_back(transform + direction.scaled(length / 2));
    out.push_back(transform - direction.scaled(length / 2));
    return out;
}

geometry::vector planeCollider::getNormalPoint(geometry::vector point) {
    /*
    This algorithm assumes that the nearest point on a line L to another
    point P that does not lie on the line is the point where a line segment
    that passes through P also intersects L perpendicularly.  Thus we can create
    a triangle that satisfies this condition and solve different values to get
    this specific point of intersection
    */
    
    using geometry::vector;

    // Begin building the triangle with the hypoteneuse
    vector toPoint = point - transform;
    double angle = std::abs(toPoint.getAngle() - direction.getAngle());

    // Calculate the magnitude of the hypoteneuse
    double hyp = toPoint.getMagnitude();

    // Get the point on the line that the intersection occurs
    vector out = transform + direction.scaled(hyp * std::cos(angle));

    // Ensure that 'out' is on the plane, otherwise return the endpoint closest to 'out'
    vector endpoint1 = transform + direction.scaled(length/2);
    vector endpoint2 = transform - direction.scaled(length/2);

    // Since 'out' is already on the line, we only need to check one axis
    if (std::min(endpoint1.x, endpoint2.x) <= out.x && out.x <= std::max(endpoint1.x, endpoint2.x)) {
        return out;
    }

    double distanceTo1 = (endpoint1 - out).getMagnitude();
    double distanceTo2 = (endpoint2 - out).getMagnitude();

    if (distanceTo1 < distanceTo2) {
        return endpoint1;
    }
    
    return endpoint2;
}


// Begin generalCollider
generalCollider::generalCollider(geometry::vector transform, std::vector<geometry::vector> pts) {
    this->transform = transform;
    int numPts = pts.size();
    for (int i = 0; i < numPts; i++) {
        points.push_back(pts[i]);
    }
}

std::vector<geometry::vector> generalCollider::getPoints() {
    std::vector<geometry::vector> out;
    for (int i = 0; i < points.size(); i++) {
        out.push_back(points[i] + transform);
    }
    return out;
}

geometry::vector generalCollider::getNormalPoint(geometry::vector point) {
    using geometry::vector;

    // This will need optimization in the future
    vector out = transform;
    double distance = MAXFLOAT;

    for (int i = 0; i < points.size(); i++) {
        int j = i + 1;
        if (j == points.size()) {
            j = 0;
        }

        vector currentPoint = transform + points[i];
        vector nextPoint = transform + points[j];

        double currentDist = (point - currentPoint).getMagnitude();

        if (point.getAngle() == currentPoint.getAngle() && currentDist < distance) {
            out = currentPoint;
            distance = currentDist;
        }

        vector planeTransform = vectorAverage(currentPoint, nextPoint);
        vector dir = nextPoint - currentPoint;
        planeCollider edge = planeCollider(planeTransform, dir, dir.getMagnitude());

        vector candidatePoint = edge.getNormalPoint(point);
        currentDist = (point - candidatePoint).getMagnitude();

        if (currentDist < distance) {
            out = candidatePoint;
            distance = currentDist;
        }
    }

    return out;
}
};