#include "geometry.hpp"
#include <gtest/gtest.h>

using namespace geometry;

TEST(Point2DTest, DefaultConstructor) {
    Point2D p;
    EXPECT_EQ(p.x, 0.0);
    EXPECT_EQ(p.y, 0.0);
}

TEST(Point2DTest, ParameterizedConstructor) {
    Point2D p(3.5, 4.2);
    EXPECT_EQ(p.x, 3.5);
    EXPECT_EQ(p.y, 4.2);
}

TEST(Point2DTest, Equality) {
    Point2D p1(1.0, 2.0);
    Point2D p2(1.0, 2.0);
    Point2D p3(2.0, 3.0);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(Point2DTest, Addition) {
    Point2D p1(1.0, 2.0);
    Point2D p2(3.0, 4.0);
    Point2D result = p1 + p2;

    EXPECT_EQ(result.x, 4.0);
    EXPECT_EQ(result.y, 6.0);
}

TEST(Point2DTest, Subtraction) {
    Point2D p1(5.0, 7.0);
    Point2D p2(2.0, 3.0);
    Point2D result = p1 - p2;

    EXPECT_EQ(result.x, 3.0);
    EXPECT_EQ(result.y, 4.0);
}

TEST(Point2DTest, ScalarMultiplication) {
    Point2D p(2.0, 3.0);
    Point2D result = p * 2.0;

    EXPECT_EQ(result.x, 4.0);
    EXPECT_EQ(result.y, 6.0);
}

TEST(Point2DTest, ScalarDivision) {
    Point2D p(4.0, 6.0);
    Point2D result = p / 2.0;

    EXPECT_EQ(result.x, 2.0);
    EXPECT_EQ(result.y, 3.0);
}

TEST(Point2DTest, DotProduct) {
    Point2D p1(1.0, 2.0);
    Point2D p2(3.0, 4.0);
    double result = p1.Dot(p2);

    EXPECT_EQ(result, 11.0);  // 1*3 + 2*4 = 11
}

TEST(Point2DTest, CrossProduct) {
    Point2D p1(1.0, 0.0);
    Point2D p2(0.0, 1.0);
    double result = p1.Cross(p2);

    EXPECT_EQ(result, 1.0);  // 1*1 - 0*0 = 1
}

TEST(Point2DTest, Length) {
    Point2D p(3.0, 4.0);
    double result = p.Length();

    EXPECT_DOUBLE_EQ(result, 5.0);  // sqrt(9 + 16) = 5
}

TEST(Point2DTest, DistanceTo) {
    Point2D p1(0.0, 0.0);
    Point2D p2(3.0, 4.0);
    double result = p1.DistanceTo(p2);

    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(Point2DTest, Normalize) {
    Point2D p(3.0, 4.0);
    Point2D normalized = p.Normalize();

    EXPECT_DOUBLE_EQ(normalized.x, 0.6);
    EXPECT_DOUBLE_EQ(normalized.y, 0.8);
}

TEST(LineTest, Constructor) {
    Point2D start(0.0, 0.0);
    Point2D end(3.0, 4.0);
    Line line(start, end);

    EXPECT_EQ(line.start, start);
    EXPECT_EQ(line.end, end);
}

TEST(LineTest, Length) {
    Line line({0.0, 0.0}, {3.0, 4.0});
    EXPECT_DOUBLE_EQ(line.Length(), 5.0);
}

TEST(LineTest, BoundingBox) {
    Line line({1.0, 2.0}, {5.0, 6.0});
    BoundingBox box = line.BoundBox();

    EXPECT_EQ(box.min_x, 1.0);
    EXPECT_EQ(box.min_y, 2.0);
    EXPECT_EQ(box.max_x, 5.0);
    EXPECT_EQ(box.max_y, 6.0);
}

TEST(LineTest, Vertices) {
    Line line({1.0, 2.0}, {3.0, 4.0});
    auto vertices = line.Vertices();

    EXPECT_EQ(vertices.size(), 2);
    EXPECT_EQ(vertices[0], Point2D(1.0, 2.0));
    EXPECT_EQ(vertices[1], Point2D(3.0, 4.0));
}

TEST(TriangleTest, Constructor) {
    Triangle tri({0, 0}, {4, 0}, {2, 3});
    EXPECT_EQ(tri.a, Point2D(0, 0));
    EXPECT_EQ(tri.b, Point2D(4, 0));
    EXPECT_EQ(tri.c, Point2D(2, 3));
}

TEST(TriangleTest, Area) {
    Triangle tri({0, 0}, {4, 0}, {2, 3});
    EXPECT_DOUBLE_EQ(tri.Area(), 6.0);  // (4 * 3) / 2 = 6
}

TEST(TriangleTest, Vertices) {
    Triangle tri({0, 0}, {4, 0}, {2, 3});
    auto vertices = tri.Vertices();

    EXPECT_EQ(vertices.size(), 3);
    EXPECT_EQ(vertices[0], Point2D(0, 0));
    EXPECT_EQ(vertices[1], Point2D(4, 0));
    EXPECT_EQ(vertices[2], Point2D(2, 3));
}

TEST(TriangleTest, BoundingBox) {
    Triangle tri({0, 0}, {4, 0}, {2, 3});
    BoundingBox box = tri.BoundBox();

    EXPECT_EQ(box.min_x, 0);
    EXPECT_EQ(box.min_y, 0);
    EXPECT_EQ(box.max_x, 4);
    EXPECT_EQ(box.max_y, 3);
}

TEST(RectangleTest, Constructor) {
    Rectangle rect({1, 2}, 5, 3);
    EXPECT_EQ(rect.bottom_left, Point2D(1, 2));
    EXPECT_EQ(rect.width, 5);
    EXPECT_EQ(rect.height, 3);
}

TEST(RectangleTest, TopRight) {
    Rectangle rect({1, 2}, 5, 3);
    Point2D top_right = rect.TopRight();

    EXPECT_EQ(top_right.x, 6);
    EXPECT_EQ(top_right.y, 5);
}

TEST(RectangleTest, Vertices) {
    Rectangle rect({0, 0}, 2, 2);
    auto vertices = rect.Vertices();

    EXPECT_EQ(vertices.size(), 4);
    EXPECT_EQ(vertices[0], Point2D(0, 0));
    EXPECT_EQ(vertices[1], Point2D(2, 0));
    EXPECT_EQ(vertices[2], Point2D(2, 2));
    EXPECT_EQ(vertices[3], Point2D(0, 2));
}

TEST(RectangleTest, BoundingBox) {
    Rectangle rect({1, 2}, 5, 3);
    BoundingBox box = rect.BoundBox();

    EXPECT_EQ(box.min_x, 1);
    EXPECT_EQ(box.min_y, 2);
    EXPECT_EQ(box.max_x, 6);
    EXPECT_EQ(box.max_y, 5);
}

TEST(CircleTest, Constructor) {
    Circle circle({1, 2}, 5);
    EXPECT_EQ(circle.center_p, Point2D(1, 2));
    EXPECT_EQ(circle.radius, 5);
}

TEST(CircleTest, BoundingBox) {
    Circle circle({0, 0}, 3);
    BoundingBox box = circle.BoundBox();

    EXPECT_EQ(box.min_x, -3);
    EXPECT_EQ(box.min_y, -3);
    EXPECT_EQ(box.max_x, 3);
    EXPECT_EQ(box.max_y, 3);
}

TEST(CircleTest, Vertices) {
    Circle circle({0, 0}, 1);
    auto vertices = circle.Vertices(4);

    EXPECT_EQ(vertices.size(), 4);
}

TEST(BoundingBoxTest, Constructor) {
    BoundingBox box(0, 1, 2, 3);
    EXPECT_EQ(box.min_x, 0);
    EXPECT_EQ(box.min_y, 1);
    EXPECT_EQ(box.max_x, 2);
    EXPECT_EQ(box.max_y, 3);
}

TEST(BoundingBoxTest, Overlaps) {
    BoundingBox box1(0, 0, 2, 2);
    BoundingBox box2(1, 1, 3, 3);
    BoundingBox box3(3, 3, 5, 5);

    EXPECT_TRUE(box1.Overlaps(box2));
    EXPECT_FALSE(box1.Overlaps(box3));
}

TEST(BoundingBoxTest, Width) {
    BoundingBox box(1, 2, 5, 6);
    EXPECT_EQ(box.Width(), 4);
}

TEST(BoundingBoxTest, Height) {
    BoundingBox box(1, 2, 5, 6);
    EXPECT_EQ(box.Height(), 4);
}

TEST(BoundingBoxTest, Center) {
    BoundingBox box(0, 0, 4, 4);
    Point2D center = box.Center();

    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 2);
}

TEST(PolygonTest, Constructor) {
    std::vector<Point2D> points = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Polygon poly(points);

    auto vertices = poly.Vertices();
    EXPECT_EQ(vertices.size(), 4);
}

TEST(PolygonTest, BoundingBox) {
    std::vector<Point2D> points = {{0, 0}, {3, 0}, {3, 4}, {0, 4}};
    Polygon poly(points);

    BoundingBox box = poly.BoundBox();
    EXPECT_EQ(box.min_x, 0);
    EXPECT_EQ(box.max_x, 3);
    EXPECT_EQ(box.min_y, 0);
    EXPECT_EQ(box.max_y, 4);
}

TEST(PolygonTest, Center) {
    std::vector<Point2D> points = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    Polygon poly(points);

    Point2D center = poly.Center();
    EXPECT_EQ(center.x, 2);
    EXPECT_EQ(center.y, 2);
}

TEST(RegularPolygonTest, Constructor) {
    RegularPolygon poly({0, 0}, 1, 6);
    EXPECT_EQ(poly.center_p, Point2D(0, 0));
    EXPECT_EQ(poly.radius, 1);
    EXPECT_EQ(poly.sides, 6);
}

TEST(RegularPolygonTest, Vertices) {
    RegularPolygon poly({0, 0}, 1, 4);
    auto vertices = poly.Vertices();

    EXPECT_EQ(vertices.size(), 4);
}

TEST(RegularPolygonTest, BoundingBox) {
    RegularPolygon poly({0, 0}, 2, 4);
    BoundingBox box = poly.BoundBox();

    EXPECT_EQ(box.min_x, -2);
    EXPECT_EQ(box.max_x, 2);
    EXPECT_EQ(box.min_y, -2);
    EXPECT_EQ(box.max_y, 2);
}