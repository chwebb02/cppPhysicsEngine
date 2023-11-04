#include "../include/physObj.h"
#include <vector>

namespace physics {
void dynamicObj::step(double delta) {
    using geometry::vector;

    vector acceleration = force / mass;
    velocity += acceleration.scaled(delta);

    position += velocity.scaled(delta);
}
};