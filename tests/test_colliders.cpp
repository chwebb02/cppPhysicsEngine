#include <gtest/gtest.h>
#include "collider.h"

TEST (circleCollider, collideWithOtherCircle) {
	using namespace physics;

	circleCollider c1 = {{0, 0}, 1};
	circleCollider c2 = {{0, 2}, 1.5};

	bool isColliding = collider::isColliding(c1, c2);
	EXPECT_EQ(true, isColliding);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}