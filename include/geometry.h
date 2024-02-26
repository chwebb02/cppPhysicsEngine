#pragma once

namespace geometry {
class vector {
private:

public:
    double x, y;

    vector(double x, double y);

    double getMagnitude();                              // Gets the length of the vector
    double getAngle();                                  // Gets the angle in radians

    vector normalized();                                // Returns a normalized vector with direction of calling vector
    vector scaled(double scalar);                       // Returns a scaled vector with direction of calling vector
    vector absoluteScaled(double scalar);               // Returns a vector in same direction scaled to magnitude equal to scalar

    vector rotatedTo(double radians);                   // Returns a vector that has been rotated to the angle in radians
    vector rotatedBy(double radians);                   // Returns a vector that has been rotated by the angle in radians

    vector operator+(vector other);                     // Add two vectors
    vector operator-(vector other);                     // Subtract two vectors (add v1 and -1 * v2)
    bool operator==(vector other);                      // Compare if two vectors have the same x and y values
    vector operator*(double scalar);                    // Scale a vector
    void operator+=(vector other);                      // Add to a vector
    void operator-=(vector other);                      // Subtract from a vector
    vector operator/(double scalar);                    // Scale a vector inversely

    static double dotProduct(vector& v1, vector& v2);   // Take the dot product of two vectors
};
};