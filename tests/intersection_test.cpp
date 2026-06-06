#include "intersections.hpp"
#include <gtest/gtest.h>

using namespace geometry;
using namespace geometry::intersections;

// ========== Line & Line ТЕСТЫ ==========

TEST(LineLineIntersectionTest, SimpleIntersection) {
    Line line1({0, 0}, {2, 2});
    Line line2({0, 2}, {2, 0});

    IntersectionVisitor visitor;
    auto result = visitor(line1, line2);

    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result.value().x, 1.0);
    EXPECT_DOUBLE_EQ(result.value().y, 1.0);
}

TEST(LineLineIntersectionTest, HorizontalVertical) {
    Line horizontal({0, 1}, {2, 1});
    Line vertical({1, 0}, {1, 2});

    IntersectionVisitor visitor;
    auto result = visitor(horizontal, vertical);

    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result.value().x, 1.0);
    EXPECT_DOUBLE_EQ(result.value().y, 1.0);
}

TEST(LineLineIntersectionTest, ParallelLines) {
    Line line1({0, 0}, {1, 1});
    Line line2({0, 1}, {1, 2});

    IntersectionVisitor visitor;
    auto result = visitor(line1, line2);

    EXPECT_FALSE(result.has_value());
}

TEST(LineLineIntersectionTest, CollinearLines) {
    Line line1({0, 0}, {2, 2});
    Line line2({1, 1}, {3, 3});

    IntersectionVisitor visitor;
    auto result = visitor(line1, line2);

    EXPECT_FALSE(result.has_value());
}

TEST(LineLineIntersectionTest, PerpendicularLines) {
    Line line1({0, 0}, {2, 0});
    Line line2({1, -1}, {1, 1});

    IntersectionVisitor visitor;
    auto result = visitor(line1, line2);

    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result.value().x, 1.0);
    EXPECT_DOUBLE_EQ(result.value().y, 0.0);
}

TEST(LineLineIntersectionTest, NegativeCoordinates) {
    Line line1({-2, -2}, {2, 2});
    Line line2({-2, 2}, {2, -2});

    IntersectionVisitor visitor;
    auto result = visitor(line1, line2);

    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result.value().x, 0.0);
    EXPECT_DOUBLE_EQ(result.value().y, 0.0);
}

// ========== Line & Circle ТЕСТЫ ==========

TEST(LineCircleIntersectionTest, TwoIntersections) {
    Line line({-2, 0}, {2, 0});
    Circle circle({0, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());
}

TEST(LineCircleIntersectionTest, OneIntersection) {
    Line line({0, 1}, {2, 1});
    Circle circle({0, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(LineCircleIntersectionTest, NoIntersection) {
    Line line({0, 2}, {2, 2});
    Circle circle({0, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_FALSE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(LineCircleIntersectionTest, LinePassesThroughCenter) {
    Line line({-2, 0}, {2, 0});
    Circle circle({0, 0}, 2);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());

    // Проверяем, что точки на окружности
    double dist1 = result.first.value().DistanceTo(circle.Center());
    double dist2 = result.second.value().DistanceTo(circle.Center());

    EXPECT_DOUBLE_EQ(dist1, circle.radius);
    EXPECT_DOUBLE_EQ(dist2, circle.radius);
}

TEST(LineCircleIntersectionTest, VerticalLine) {
    Line line({1, -2}, {1, 2});
    Circle circle({0, 0}, 2);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());
}

TEST(LineCircleIntersectionTest, DiagonalLine) {
    Line line({-1, -1}, {1, 1});
    Circle circle({0, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());
}

// ========== Circle & Circle ТЕСТЫ ==========

TEST(CircleCircleIntersectionTest, TwoIntersections) {
    Circle circle1({0, 0}, 2);
    Circle circle2({2, 0}, 2);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());
}

TEST(CircleCircleIntersectionTest, OneIntersection) {
    Circle circle1({0, 0}, 1);
    Circle circle2({2, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(CircleCircleIntersectionTest, NoIntersection) {
    Circle circle1({0, 0}, 1);
    Circle circle2({5, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_FALSE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(CircleCircleIntersectionTest, OneInsideAnother) {
    Circle circle1({0, 0}, 5);
    Circle circle2({0, 0}, 2);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_FALSE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(CircleCircleIntersectionTest, Concentric) {
    Circle circle1({0, 0}, 1);
    Circle circle2({0, 0}, 2);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_FALSE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(CircleCircleIntersectionTest, SymmetricIntersection) {
    Circle circle1({-1, 0}, 1.5);
    Circle circle2({1, 0}, 1.5);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());

    // Проверяем симметрию относительно оси X
    EXPECT_DOUBLE_EQ(result.first.value().x, result.second.value().x);
    EXPECT_DOUBLE_EQ(std::abs(result.first.value().y), std::abs(result.second.value().y));
}

TEST(CircleCircleIntersectionTest, LargeAndSmallCircles) {
    Circle large({0, 0}, 10);
    Circle small({5, 0}, 3);

    IntersectionVisitor visitor;
    auto result = visitor(large, small);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_TRUE(result.second.has_value());
}

// ========== INVALID COMBINATIONS ТЕСТЫ ==========

TEST(IntersectionInvalidTest, LineTriangle) {
    Line line({0, 0}, {2, 2});
    Triangle triangle({0, 0}, {2, 0}, {1, 2});

    IntersectionVisitor visitor;
    EXPECT_THROW(visitor(line, triangle), std::logic_error);
}

TEST(IntersectionInvalidTest, CircleRectangle) {
    Circle circle({0, 0}, 1);
    Rectangle rect({-2, -2}, 4, 4);

    IntersectionVisitor visitor;
    EXPECT_THROW(visitor(circle, rect), std::logic_error);
}

TEST(IntersectionInvalidTest, TrianglePolygon) {
    Triangle tri({0, 0}, {2, 0}, {1, 2});
    std::vector<Point2D> points = {{0, 0}, {3, 0}, {3, 3}, {0, 3}};
    Polygon poly(points);

    IntersectionVisitor visitor;
    EXPECT_THROW(visitor(tri, poly), std::logic_error);
}

TEST(IntersectionInvalidTest, LineRectangle) {
    Line line({0, 0}, {2, 2});
    Rectangle rect({0, 0}, 2, 2);

    IntersectionVisitor visitor;
    EXPECT_THROW(visitor(line, rect), std::logic_error);
}

// ========== EDGE CASES ==========

TEST(IntersectionEdgeCasesTest, VeryCloseCircles) {
    Circle circle1({0, 0}, 1);
    Circle circle2({1.9999, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_TRUE(result.first.has_value() || result.second.has_value());
}

TEST(IntersectionEdgeCasesTest, CircleWithZeroRadius) {
    Circle circle1({0, 0}, 0);
    Circle circle2({0, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(circle1, circle2);

    EXPECT_FALSE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}

TEST(IntersectionEdgeCasesTest, LineCircleTangent) {
    Line line({0, 1}, {2, 1});
    Circle circle({1, 0}, 1);

    IntersectionVisitor visitor;
    auto result = visitor(line, circle);

    EXPECT_TRUE(result.first.has_value());
    EXPECT_FALSE(result.second.has_value());
}