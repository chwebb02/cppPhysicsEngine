#include "../include/geometry.h"
#include <math.h>

namespace geometry {
vector::vector(double x, double y) {
    this->x = x;
    this->y = y;
}

double vector::getMagnitude() {
    return std::sqrt(x * x + y * y);
}

double vector::getAngle() {
    return std::atan2(y, x);
}

vector vector::normalized() {
    return scaled(1 / getMagnitude());
}

vector vector::scaled(double scalar) {
    return vector(x * scalar, y * scalar);
}

vector vector::rotatedTo(double radians) {
    double magnitude = getMagnitude();

    return vector(magnitude * std::cos(radians), magnitude * std::sin(radians));
}

vector vector::rotatedBy(double radians) {
    radians += getAngle();
    return rotatedTo(radians);
}

vector vector::operator+(vector& other) {
    return vector(x + other.x, y + other.y);
}

vector vector::operator-(vector& other) {
    vector invOther = other.scaled(-1);
    return operator+(invOther);
}
};