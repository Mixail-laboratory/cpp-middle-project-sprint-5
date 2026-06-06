#include "convex_hull.hpp"
#include "geometry.hpp"
#include <gtest/gtest.h>

using namespace geometry;
using namespace convex_hull;

TEST(ConvexHullTest, SimpleSquare) {
    std::vector<Point2D> points = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 4);
}

TEST(ConvexHullTest, Triangle) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {1, 2}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 3);
}

TEST(ConvexHullTest, PointInside) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {1, 1}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 4);
}

TEST(ConvexHullTest, CollinearPoints) {
    std::vector<Point2D> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 4);
}

TEST(ConvexHullTest, LessThanThreePoints) {
    std::vector<Point2D> points = {{0, 0}, {1, 1}};

    auto result = GrahamScan(std::span(points));
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "At least three points are required for convex hull.");
}

TEST(ConvexHullTest, Pentagon) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {3, 1.5}, {1.5, 3}, {-0.5, 1.5}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 5);
}

TEST(ConvexHullTest, RandomWithInside) {
    std::vector<Point2D> points = {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {1, 1}, {2, 2}, {3, 3}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 4);
}

TEST(ConvexHullTest, SamePoints) {
    std::vector<Point2D> points = {{1, 1}, {1, 1}, {1, 1}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_GE(hull.size(), 1);
}

TEST(ConvexHullTest, StarShape) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}, {1, 0.5}, {1.5, 1}, {1, 1.5}, {0.5, 1}};

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 4);
}

TEST(ConvexHullTest, ManyPoints) {
    std::vector<Point2D> points;

    for (int i = 0; i < 20; ++i) {
        double angle = 2 * M_PI * i / 20;
        points.push_back({std::cos(angle), std::sin(angle)});
    }
    points.push_back({0, 0});

    auto result = GrahamScan(std::span(points));
    ASSERT_TRUE(result.has_value());

    auto hull = result.value();
    EXPECT_EQ(hull.size(), 20);
}