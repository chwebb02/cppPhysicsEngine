#pragma once

#include "vector.h"

namespace geometry {
class line {
private:
	double A, B, C;
public:
	line(vector pt1, vector pt2);
	
	double yAt(double x);
	double xAt(double y);
};
};