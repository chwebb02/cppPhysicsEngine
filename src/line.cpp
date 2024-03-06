#include "line.h"

namespace geometry {
line::line(vector p1, vector p2) {
	A = (p2.y - p1.y);
	B = (p1.x - p2.x);
	C = A * p1.x + B * p1.y;
}

double line::yAt(double x) {
	return (C - (A * x)) / B;
}

double line::xAt(double y) {
	return (C - (B * y)) / A;
}
};