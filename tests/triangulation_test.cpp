#include "triangulation.hpp"
#include <gtest/gtest.h>

using namespace geometry::triangulation;

TEST(DelaunayTriangulationTest, SimpleTriangle) {
    std::vector<Point2D> points = {{0, 0}, {4, 0}, {2, 3}};

    auto result = DelaunayTriangulation(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto triangles = result.value();
    EXPECT_GT(triangles.size(), 0);
}

TEST(DelaunayTriangulationTest, Square) {
    std::vector<Point2D> points = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

    auto result = DelaunayTriangulation(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto triangles = result.value();
    EXPECT_EQ(triangles.size(), 2);
}

TEST(DelaunayTriangulationTest, TooFewPoints) {
    std::vector<Point2D> points = {{0, 0}, {1, 1}};

    auto result = DelaunayTriangulation(std::span(points));
    EXPECT_FALSE(result.has_value());
}

TEST(DelaunayTriangulationTest, Pentagon) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {3, 1.5}, {1.5, 3}, {-0.5, 1.5}};

    auto result = DelaunayTriangulation(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto triangles = result.value();
    EXPECT_GT(triangles.size(), 0);
}

// ========== DELAUNAY TRIANGLE ТЕСТЫ ==========

TEST(DelaunayTriangleTest, Circumcenter) {
    DelaunayTriangle tri({0, 0}, {4, 0}, {2, 3});
    Point2D center = tri.Circumcenter();

    EXPECT_GT(center.x, 0);
    EXPECT_GT(center.y, 0);
}

TEST(DelaunayTriangleTest, Circumradius) {
    DelaunayTriangle tri({0, 0}, {4, 0}, {2, 3});
    double radius = tri.Circumradius();

    EXPECT_GT(radius, 0);
}

TEST(DelaunayTriangleTest, ContainsPoint) {
    DelaunayTriangle tri({0, 0}, {4, 0}, {2, 3});
    Point2D center = tri.Circumcenter();

    EXPECT_TRUE(tri.ContainsPoint(center));
}

TEST(DelaunayTriangleTest, SharesEdge) {
    DelaunayTriangle tri1({0, 0}, {4, 0}, {2, 3});
    DelaunayTriangle tri2({0, 0}, {4, 0}, {2, -3});

    EXPECT_TRUE(tri1.SharesEdge(tri2));
}