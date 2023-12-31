#pragma once

namespace geometry {
class vector {
private:

public:
    double x, y;

    vector(double x, double y);

    double getMagnitude();  // Gets the length of the vector
    double getAngle();      // Gets the angle in radians

    vector normalized();                    // Returns a normalized vector with direction of calling vector
    vector scaled(double scalar);           // Returns a scaled vector with direction of calling vector
    vector absoluteScaled(double scalar);   // Returns a vector in same direction scaled to magnitude equal to scalar

    vector rotatedTo(double radians);      // Returns a vector that has been rotated to the angle in radians
    vector rotatedBy(double radians);      // Returns a vector that has been rotated by the angle in radians

    vector operator+(vector other);
    vector operator-(vector other);
    bool operator==(vector other);
    vector operator*(double scalar);
    void operator+=(vector other);
    void operator-=(vector other);
    vector operator/(double scalar);

    static double dotProduct(vector& v1, vector& v2);
};
};