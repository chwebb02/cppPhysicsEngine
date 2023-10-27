#include "../include/collider.h"
#include "../include/geometry.h"
#include <math.h>
#include <vector>
#include <iostream>

namespace physics {
collider::collider(geometry::vector transform) : transform(0, 0) {
    this->transform = transform;
}

collider::collider() : transform(0, 0) {}

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
circleCollider::circleCollider(geometry::vector transform, double radius) {
    this->transform = transform;
    this->radius = radius;
}


geometry::vector circleCollider::nearestTo(collider &other) {
    using geometry::vector;

    vector toOther = other.getTransform() - transform;
    return toOther.absoluteScaled(radius) + transform;
}

std::vector<geometry::vector> circleCollider::getPoints() {
    std::vector<geometry::vector> out;
    out.push_back(transform);
    return out;
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

geometry::vector planeCollider::nearestTo(collider& other) {
    using geometry::vector;

    vector out = transform;
    std::vector<vector> otherPoints = other.getPoints();

    // Find the nearest point on the line to each point on the otherCollider
    int numOtherPoints = otherPoints.size();
    double distance = MAXFLOAT;
    for (int i = 0; i < numOtherPoints; i++) {
        /*
        This algorithm assumes that the nearest point on a line L to another
        point P that does not lie on the line is the point where a line segment
        that passes through P also intersects L perpendicularly.  Thus we can create
        a triangle that satisfies this condition and solve different values to get
        this specific point of intersection
        */

        // Get the vector that will serve as our hypoteneuse
        vector toCurrentPoint = otherPoints[i] - transform;
        double angleBetween = std::abs(direction.getAngle() - toCurrentPoint.getAngle());


        // Get the acute angle to form a triangle with assume right angle
        while (angleBetween > M_PI / 2) {
            angleBetween -= (M_PI / 2);
        }

        // Calculate the distance to the point that can make this triangle
        double hyp = toCurrentPoint.getMagnitude();
        double currentDist = hyp * std::cos(angleBetween);

        // If the distance is less than the current least, set the least to current
        if (currentDist < distance) {
            distance = currentDist;
            out = direction.scaled(hyp * std::sin(angleBetween)) + transform;
        } else if (distance == currentDist) {       // This may need to be reworked with tolerances
            out = vectorAverage(out, direction.scaled(hyp * std::sin(angleBetween)) + transform);
        }
    }

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

std::vector<geometry::vector> planeCollider::getPoints() {
    std::vector<geometry::vector> out;
    out.push_back(transform);
    out.push_back(transform + direction.scaled(length / 2));
    out.push_back(transform - direction.scaled(length / 2));
    return out;
}


// Begin generalCollider
generalCollider::generalCollider(geometry::vector transform, std::vector<geometry::vector> pts) {
    this->transform = transform;
    int numPts = pts.size();
    for (int i = 0; i < numPts; i++) {
        points.push_back(pts[i]);
    }
}

geometry::vector generalCollider::nearestTo(collider &other) {
    using geometry::vector;

    int numEdges = points.size();
    vector out = transform;
    double distance = MAXFLOAT;

    std::vector<vector> otherPoints = other.getPoints();
    int numOtherPoints = otherPoints.size();

    for (int i = 0; i < numEdges; i++) {
        // Get the next index
        int next = i + 1;
        if (next == numEdges) {
            next = 0;
        }

        // We will create a planeCollider to test each edge
        vector planeTransform = vectorAverage(points[i] + transform, points[next] + transform);
        planeCollider *edge = new planeCollider(planeTransform, (points[i] - points[next]), (points[i] - points[next]).getMagnitude());

        // Get the closest point on the edge
        vector candidatePoint = edge->nearestTo(other);
        delete edge;
        
        // Calculate distance from each point on other, keep shortest
        double shortest = MAXFLOAT;
        for (int j = 0; j < numOtherPoints; j++) {
            double currentDist = (candidatePoint - otherPoints[j]).getMagnitude();

            if (currentDist < shortest) {
                shortest = currentDist;
            }
        }

        // If the point on this edge is closer to the other collider than the last, update it as such
        if (shortest < distance) {
            distance = shortest;
            out = candidatePoint;
        } else if (shortest == distance) {      // This may need to be reworked with tolerances
            out = vectorAverage(out, candidatePoint);
        }
    }

    return out;
}

std::vector<geometry::vector> generalCollider::getPoints() {
    std::vector<geometry::vector> out = std::vector<geometry::vector>(points);
    out.push_back(transform);
    return out;
}
};