#include "convex_hull.hpp"
#include "geometry.hpp"
#include "intersections.hpp"
#include "queries.hpp"
#include "shape_utils.hpp"
#include "triangulation.hpp"
#include "visualization.hpp"

#include <algorithm>
#include <iterator>
#include <print>
#include <random>
#include <ranges>
#include <vector>

using namespace geometry;

void PrintAllIntersections(const Shape &shape, std::span<const Shape> others) {
    std::println("\n=== Intersections ===");
    auto intersecting = others | std::views::filter([&shape](const Shape &iShape) {
                            return queries::GetBoundBox(shape).Overlaps(queries::GetBoundBox(iShape));
                        });
    std::ranges::for_each(intersecting,
                          [&shape](const Shape &other) { std::println("Shape {} intersects with {}", shape, other); });
}

void PrintDistancesFromPointToShapes(Point2D p, std::span<const Shape> shapes) {
    std::println("\n=== Distance from Point Test ===");
    std::vector<Shape> temp;
    temp.reserve(5);
    auto gen = std::mt19937{std::random_device{}()};
    std::ranges::sample(shapes, std::back_inserter(temp), 5, gen);

    std::ranges::for_each(temp, [&p](const Shape &iShape) {
        std::println("Distance from point {} to shape {}, equal {:.2f}", p, iShape,
                     queries::DistanceToPoint(iShape, p));
    });
}

void PerformShapeAnalysis(std::span<const Shape> shapes) {
    std::println("\n=== Shape Analysis ===");

    std::ranges::for_each(utils::FindAllCollisions(shapes),
                          [](const auto &pair) { std::println("  {} intersects {}", pair.first, pair.second); });

    auto highIdx = utils::FindHighestShape(shapes);

    std::println("max high shape: {}", shapes[*highIdx]);
    if (shapes.size() > 1) {
        auto distance = queries::DistanceBetweenShapes(shapes[0], shapes[1]);
        if (distance.has_value()) {
            std::println("Distance between first two shapes: {:.2f}", distance.value());
        } else {
            std::println("Distance calculation not supported for these shapes");
        }
    }
}

void PerformExtraShapeAnalysis(std::span<const Shape> shapes) {
    std::println("\n=== Shape Extra Analysis ===");
    std::vector<Shape> out;
    auto gen = std::mt19937{std::random_device{}()};
    std::ranges::sample(
        std::views::filter(shapes, [](const Shape &iShape) { return queries::GetHeight(iShape) > 50.0; }),
        std::back_inserter(out), 3, gen);
    std::ranges::for_each(
        out, [](const Shape &iShape) { std::println("{} - height {:.2f}", iShape, queries::GetHeight(iShape)); });
    auto minIt = std::ranges::min_element(
        shapes, [](const Shape &lhs, const Shape &rhs) { return queries::GetHeight(lhs) < queries::GetHeight(rhs); });

    auto highIdx = utils::FindHighestShape(shapes);

    std::println("min high shape: {}", *minIt);
    std::println("max high shape: {}", shapes[*highIdx]);
}

int main() {
    std::vector<Shape> shapes = utils::ParseShapes("circle 0 0 1.5; line 1 2 3 4; polygon 0 0 2 5; triangle 0 0 1 0 "
                                                   "0.5 1; polygon 0 0 1 2; badshape; circle 0 0 -1");
    std::println("Parsed {} shapes", shapes.size());
    std::ranges::for_each(shapes | std::views::enumerate, [](const auto &pair) {
        auto [idx, shape] = pair;
        std::println("Shape {}: height = {:.2f}", idx, queries::GetHeight(shape));
    });
    PrintAllIntersections(shapes[0], shapes);

    PrintDistancesFromPointToShapes(Point2D{10.0, 10.0}, shapes);

    PerformShapeAnalysis(shapes);

    PerformExtraShapeAnalysis(shapes);

    geometry::visualization::Draw(shapes);

    std::vector<Point2D> points;
    std::ranges::for_each(shapes, [&points](const Shape &shape) {
        shape.visit([&points](const auto &s) { std::ranges::copy(s.Vertices(), std::back_inserter(points)); });
    });

    auto hull_result = convex_hull::GrahamScan(points);
    if (hull_result.has_value()) {
        auto hull_points = hull_result.value();
        shapes.emplace_back(Polygon{hull_points});
        std::println("Convex hull computed with {} points", hull_points.size());
        geometry::visualization::Draw(shapes);
    }

    {
        std::vector<Point2D> points = {{0, 0}, {10, 0}, {5, 8}, {15, 5}, {2, 12}};

        auto triangles = triangulation::DelaunayTriangulation(points);
        std::println("Delaunay triangulation computed with {} triangles", triangles.value().size());

        std::vector<geometry::triangulation::DelaunayTriangle> tri_shapes;
        std::ranges::copy(*triangles, std::back_inserter(tri_shapes));
        geometry::visualization::Draw(tri_shapes);
    }
    return 0;
}