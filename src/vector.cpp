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
    if (getMagnitude() == 0) {
        return *this;
    }

    return scaled(1 / getMagnitude());
}

vector vector::scaled(double scalar) {
    return vector(x * scalar, y * scalar);
}

vector vector::absoluteScaled(double scalar) {
    vector out = normalized();
    return out.scaled(scalar);
}

vector vector::rotatedTo(double radians) {
    double magnitude = getMagnitude();

    return vector(magnitude * std::cos(radians), magnitude * std::sin(radians));
}

vector vector::rotatedBy(double radians) {
    radians += getAngle();
    return rotatedTo(radians);
}

vector vector::operator+(vector other) {
    return vector(x + other.x, y + other.y);
}

vector vector::operator-(vector other) {
    vector invOther = other.scaled(-1);
    return operator+(invOther);
}

bool vector::operator==(vector other) {
    return x == other.x && y == other.y;
}

double vector::dotProduct(vector& v1, vector& v2) {
    return v1.x * v2.x + v1.y + v2.y;
}

vector vector::operator*(double scalar) {
    return scaled(scalar);
}
};