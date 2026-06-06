#include "shape_utils.hpp"
#include <gtest/gtest.h>

using namespace geometry::utils;
using namespace geometry;
TEST(MakeCircleTest, ValidCircle) {
    auto result = MakeCircle({1.0, 2.0, 3.0});
    ASSERT_TRUE(result.has_value());

    Circle circle = std::get<Circle>(result.value());
    EXPECT_EQ(circle.center_p.x, 1.0);
    EXPECT_EQ(circle.center_p.y, 2.0);
    EXPECT_EQ(circle.radius, 3.0);
}

TEST(MakeCircleTest, InvalidSize) {
    auto result = MakeCircle({1.0, 2.0});
    EXPECT_FALSE(result.has_value());
}

TEST(MakeCircleTest, NegativeRadius) {
    auto result = MakeCircle({1.0, 2.0, -3.0});
    EXPECT_FALSE(result.has_value());
}

// ========== MAKE LINE ТЕСТЫ ==========

TEST(MakeLineTest, ValidLine) {
    auto result = MakeLine({0.0, 0.0, 4.0, 3.0});
    ASSERT_TRUE(result.has_value());

    Line line = std::get<Line>(result.value());
    EXPECT_EQ(line.start.x, 0.0);
    EXPECT_EQ(line.end.x, 4.0);
}

TEST(MakeLineTest, InvalidSize) {
    auto result = MakeLine({0.0, 0.0, 4.0});
    EXPECT_FALSE(result.has_value());
}

// ========== MAKE TRIANGLE ТЕСТЫ ==========

TEST(MakeTriangleTest, ValidTriangle) {
    auto result = MakeTriangle({0.0, 0.0, 4.0, 0.0, 2.0, 3.0});
    ASSERT_TRUE(result.has_value());

    Triangle tri = std::get<Triangle>(result.value());
    EXPECT_EQ(tri.a.x, 0.0);
    EXPECT_EQ(tri.b.x, 4.0);
    EXPECT_EQ(tri.c.x, 2.0);
}

TEST(MakeTriangleTest, InvalidSize) {
    auto result = MakeTriangle({0.0, 0.0, 4.0, 0.0});
    EXPECT_FALSE(result.has_value());
}

// ========== MAKE RECTANGLE ТЕСТЫ ==========

TEST(MakeRectangleTest, ValidRectangle) {
    auto result = MakeRectangle({1.0, 2.0, 4.0, 3.0});
    ASSERT_TRUE(result.has_value());

    Rectangle rect = std::get<Rectangle>(result.value());
    EXPECT_EQ(rect.bottom_left.x, 1.0);
    EXPECT_EQ(rect.width, 4.0);
    EXPECT_EQ(rect.height, 3.0);
}

TEST(MakeRectangleTest, ZeroWidth) {
    auto result = MakeRectangle({1.0, 2.0, 0.0, 3.0});
    EXPECT_FALSE(result.has_value());
}

// ========== MAKE POLYGON ТЕСТЫ ==========

TEST(MakePolygonTest, ValidPolygon) {
    auto result = MakePolygon({0.0, 0.0, 2.0, 6.0});
    ASSERT_TRUE(result.has_value());

    RegularPolygon poly = std::get<RegularPolygon>(result.value());
    EXPECT_EQ(poly.sides, 6);
}

TEST(MakePolygonTest, InvalidSides) {
    auto result = MakePolygon({0.0, 0.0, 2.0, 2.0});
    EXPECT_FALSE(result.has_value());
}

TEST(MakePolygonTest, NonIntegerSides) {
    auto result = MakePolygon({0.0, 0.0, 2.0, 5.5});
    EXPECT_FALSE(result.has_value());
}

// ========== PARSE SHAPES ТЕСТЫ ==========

TEST(ParseShapesTest, SingleCircle) {
    auto shapes = ParseShapes("circle 0 0 5");
    EXPECT_EQ(shapes.size(), 1);
}

TEST(ParseShapesTest, MultipleShapes) {
    auto shapes = ParseShapes("circle 0 0 5; line 0 0 4 3; rectangle 1 2 4 3");
    EXPECT_EQ(shapes.size(), 3);
}

TEST(ParseShapesTest, EmptyInput) {
    auto shapes = ParseShapes("");
    EXPECT_EQ(shapes.size(), 0);
}

TEST(ParseShapesTest, InvalidShape) {
    auto shapes = ParseShapes("invalid 1 2 3");
    EXPECT_EQ(shapes.size(), 0);
}