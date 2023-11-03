#include "../include/collider.h"
#include <math.h>
#include <vector>

namespace physics {
// Constructors
circleCollider::circleCollider(geometry::vector tform, double rad) {
    transform = tform;
    radius = rad;
}

lineCollider::lineCollider(geometry::vector tform, geometry::vector dir, double len) : direction(dir.normalized()) {
    transform = tform;
    length = len;
}

generalCollider::generalCollider(geometry::vector tform, std::vector<geometry::vector> pts) {
    transform = tform;
    points = std::vector<geometry::vector>(pts);
}


// getTransform
geometry::vector collider::getTransform() {
    return transform;
}


// nearestPointTo
geometry::vector circleCollider::nearestPointToPoint(geometry::vector point) {
    using geometry::vector;
    
    vector toPoint = point - transform;

    if (toPoint.getMagnitude() < radius) {
        return point;
    }

    return transform + toPoint.absoluteScaled(radius);
}

geometry::vector lineCollider::nearestPointToPoint(geometry::vector point) {
    using geometry::vector;

    vector hypoteneuse = point - transform;
    double hypoteneuseLength = hypoteneuse.getMagnitude();
    double theta = std::abs(direction.getAngle() - hypoteneuse.getAngle());

    double delta = hypoteneuseLength * std::cos(theta);
    vector rawPoint = transform + direction.scaled(delta);

    if ((rawPoint - transform).getMagnitude() <= length / 2) {
        return rawPoint;
    }

    vector scaledDirection = direction.scaled(length / 2);
    vector endpoint1 = transform + scaledDirection;
    vector endpoint2 = transform - scaledDirection;

    if ((rawPoint - endpoint1).getMagnitude() < (rawPoint - endpoint2).getMagnitude()) {
        return endpoint1;
    }

    return endpoint2;
}

geometry::vector vectorAverage(const geometry::vector& v1, const geometry::vector& v2) {
    return geometry::vector((v1.x + v2.x) / 2, (v1.y + v2.y) / 2);
}

geometry::vector generalCollider::nearestPointToPoint(geometry::vector point) {
    using geometry::vector;

    double leastDistance = MAXFLOAT;
    vector out = transform;

    for (int i = 0, j = 1; i < points.size(); i++, j++) {
        if (j == points.size()) {
            j = 0;
        }

        vector currentPoint = transform + points[i];
        vector nextPoint = transform + points[j];

        vector lineTransform = vectorAverage(currentPoint, nextPoint);
        vector lineDirection = nextPoint - currentPoint;
        double lineMagnitude = lineDirection.getMagnitude();

        lineCollider line = lineCollider(lineTransform, lineDirection, lineMagnitude);

        vector candidatePoint = line.nearestPointToPoint(point);
        double candidateDistance = (candidatePoint - point).getMagnitude();

        if (candidateDistance < leastDistance) {
            double pointToTransform = (point - transform).getMagnitude();
            double candidateToTransform = (candidatePoint - transform).getMagnitude();

            if (pointToTransform < candidateToTransform) {
                leastDistance = pointToTransform;
                out = point;
            } else {
                leastDistance = candidateDistance;
                out = candidatePoint;
            }
        }
    }

    return out;
}


// getPoints()
std::vector<geometry::vector> circleCollider::getPoints() {
    std::vector<geometry::vector> out = {transform};
    return out;
}

std::vector<geometry::vector> lineCollider::getPoints() {
    std::vector<geometry::vector> out = {transform - direction.scaled(length / 2), transform, transform + direction.scaled(length / 2)};
    return out;
}

std::vector<geometry::vector> generalCollider::getPoints() {
    std::vector<geometry::vector> out = std::vector<geometry::vector>(points);
    return out;
}


// nearestToCollider
geometry::vector circleCollider::nearestPointToCollider(collider& other) {
    using geometry::vector;
    
    vector nearestToCircle = other.nearestPointToPoint(transform);
    vector toOtherNearest = (nearestToCircle - transform).normalized();

    return transform + toOtherNearest.scaled(radius);
}

geometry::vector collider::nearestPointToCollider(collider& other) {
    using geometry::vector;

    double leastDistance = MAXFLOAT;
    vector out = transform;

    std::vector<vector> otherPoints = other.getPoints();
    for (vector point : otherPoints) {
        vector nearestOnLine = nearestPointToPoint(point);                              // Get the nearest point on the collider to the endpoint of the other collider
        vector nearestOnOther = other.nearestPointToPoint(nearestOnLine);               // Get the nearest point on the other collider to the nearest point on this collider
        double candidateDistance = (nearestOnLine - nearestOnOther).getMagnitude();     // Find the difference in these points

        if (candidateDistance < leastDistance) {
            leastDistance = candidateDistance;
            out = nearestPointToPoint(nearestOnOther);
        }
    }

    return out;
}


// rotate
void circleCollider::rotateBy(double radians) {
    return;
}

void lineCollider::rotateBy(double radians) {
    direction = direction.rotatedBy(radians);
}

void generalCollider::rotateBy(double radians) {
    using geometry::vector;

    for (vector& pt : points) {
        pt = pt.rotatedBy(radians);
    }
}

// translate
void collider::translate(geometry::vector newPos) {
    transform = newPos;
}


// isColliding
bool collider::isColliding(collider& c1, collider& c2) {
    using geometry::vector;

    vector nearest1 = c1.nearestPointToCollider(c2);
    vector nearest2 = c2.nearestPointToCollider(c1);

    if (nearest1.getMagnitude() + nearest2.getMagnitude() >= (c1.transform - c2.transform).getMagnitude()) {
        return true;
    }

    return false;
}
};