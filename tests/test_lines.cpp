#include <gtest/gtest.h>
#include "line.h"

TEST(line, yEvaluation1) {
	using namespace geometry;

	line l = {vector(1, 1), vector(0, 0)};
	EXPECT_EQ(2, l.yAt(2));
}

TEST(line, yEvaluation2) {
	using namespace geometry;

	line l = {vector(1, 5), vector(0, 0)};
	EXPECT_EQ(10, l.yAt(2));
}

TEST(line, yEvaluation3) {
	using namespace geometry;

	line l = {vector(0, 1), vector(1, 1)};
	EXPECT_EQ(1, l.yAt(10));
}

TEST(line, xEvaluation1) {
	using namespace geometry;

	line l = {vector(0, 0), vector(0, 1)};
	EXPECT_EQ(0, l.xAt(10));
}

TEST(line, xEvaluation2) {
	using namespace geometry;

	line l = {vector(0, 0), vector(2, 3)};
	EXPECT_EQ(4, l.xAt(6));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}