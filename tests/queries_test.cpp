#include "queries.hpp"
#include <gtest/gtest.h>

// ========== DISTANCE VISITOR ТЕСТЫ ==========

TEST(DistanceVisitorTest, PointToLine) {
    Line line({0, 0}, {4, 0});
    Point2D point(2, 3);

    DistanceVisitor visitor(point);
    double distance = visitor(line);

    EXPECT_DOUBLE_EQ(distance, 3.0);
}

TEST(DistanceVisitorTest, PointToLineEndpoint) {
    Line line({0, 0}, {4, 0});
    Point2D point(0, 0);

    DistanceVisitor visitor(point);
    double distance = visitor(line);

    EXPECT_DOUBLE_EQ(distance, 0.0);
}

TEST(DistanceVisitorTest, PointToCircle) {
    Circle circle({0, 0}, 2);
    Point2D point(5, 0);

    DistanceVisitor visitor(point);
    double distance = visitor(circle);

    EXPECT_DOUBLE_EQ(distance, 3.0);  // 5 - 2 = 3
}

TEST(DistanceVisitorTest, PointInsideCircle) {
    Circle circle({0, 0}, 5);
    Point2D point(0, 0);

    DistanceVisitor visitor(point);
    double distance = visitor(circle);

    EXPECT_DOUBLE_EQ(distance, 0.0);
}

TEST(DistanceVisitorTest, PointToTriangle) {
    Triangle triangle({0, 0}, {4, 0}, {2, 3});
    Point2D point(2, 5);

    DistanceVisitor visitor(point);
    double distance = visitor(triangle);

    EXPECT_GT(distance, 0.0);
}

TEST(DistanceVisitorTest, PointToRectangle) {
    Rectangle rect({0, 0}, 4, 3);
    Point2D point(5, 1.5);

    DistanceVisitor visitor(point);
    double distance = visitor(rect);

    EXPECT_DOUBLE_EQ(distance, 1.0);
}

// ========== POINT IN SHAPE VISITOR ТЕСТЫ ==========

TEST(PointInShapeVisitorTest, PointOnLine) {
    Line line({0, 0}, {4, 0});
    Point2D point(2, 0);

    PointInShapeVisitor visitor(point);
    EXPECT_TRUE(visitor(line));
}

TEST(PointInShapeVisitorTest, PointNotOnLine) {
    Line line({0, 0}, {4, 0});
    Point2D point(2, 1);

    PointInShapeVisitor visitor(point);
    EXPECT_FALSE(visitor(line));
}

TEST(PointInShapeVisitorTest, PointInTriangle) {
    Triangle triangle({0, 0}, {4, 0}, {2, 4});
    Point2D point(2, 1);

    PointInShapeVisitor visitor(point);
    EXPECT_TRUE(visitor(triangle));
}

TEST(PointInShapeVisitorTest, PointOutsideTriangle) {
    Triangle triangle({0, 0}, {4, 0}, {2, 4});
    Point2D point(0, 5);

    PointInShapeVisitor visitor(point);
    EXPECT_FALSE(visitor(point));
}

TEST(PointInShapeVisitorTest, PointInRectangle) {
    Rectangle rect({0, 0}, 4, 3);
    Point2D point(2, 1.5);

    PointInShapeVisitor visitor(point);
    EXPECT_TRUE(visitor(rect));
}

TEST(PointInShapeVisitorTest, PointOutsideRectangle) {
    Rectangle rect({0, 0}, 4, 3);
    Point2D point(5, 1.5);

    PointInShapeVisitor visitor(point);
    EXPECT_FALSE(visitor(rect));
}

TEST(PointInShapeVisitorTest, PointInCircle) {
    Circle circle({0, 0}, 5);
    Point2D point(2, 2);

    PointInShapeVisitor visitor(point);
    EXPECT_TRUE(visitor(circle));
}

TEST(PointInShapeVisitorTest, PointOnCircleBoundary) {
    Circle circle({0, 0}, 5);
    Point2D point(5, 0);

    PointInShapeVisitor visitor(point);
    EXPECT_TRUE(visitor(circle));
}

// ========== BOUNDING BOX ТЕСТЫ ==========

TEST(BoundingBoxQueryTest, LineBox) {
    Line line({1, 2}, {5, 6});
    BoundingBox box = GetBoundBox(line);

    EXPECT_EQ(box.min_x, 1);
    EXPECT_EQ(box.min_y, 2);
    EXPECT_EQ(box.max_x, 5);
    EXPECT_EQ(box.max_y, 6);
}

TEST(BoundingBoxQueryTest, CircleBox) {
    Circle circle({0, 0}, 3);
    BoundingBox box = GetBoundBox(circle);

    EXPECT_EQ(box.min_x, -3);
    EXPECT_EQ(box.min_y, -3);
    EXPECT_EQ(box.max_x, 3);
    EXPECT_EQ(box.max_y, 3);
}

TEST(BoundingBoxQueryTest, RectangleBox) {
    Rectangle rect({1, 2}, 4, 3);
    BoundingBox box = GetBoundBox(rect);

    EXPECT_EQ(box.min_x, 1);
    EXPECT_EQ(box.min_y, 2);
    EXPECT_EQ(box.max_x, 5);
    EXPECT_EQ(box.max_y, 5);
}

// ========== HEIGHT QUERY ТЕСТЫ ==========

TEST(HeightQueryTest, RectangleHeight) {
    Rectangle rect({0, 0}, 4, 3);
    double height = GetHeight(rect);

    EXPECT_EQ(height, 3);
}

TEST(HeightQueryTest, CircleHeight) {
    Circle circle({0, 0}, 5);
    double height = GetHeight(circle);

    EXPECT_EQ(height, 10);
}
