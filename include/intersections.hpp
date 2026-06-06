#pragma once
#include "geometry.hpp"
#include <cmath>
#include <optional>
#include <stdexcept>

namespace geometry::intersections {

/*
 * Класс для поиска пересечений между двумя фигурами
 *
 * Требуется организовать возможность нахождения пересечений только для следующих комбинаций фигур:
 *    - Line   & Line
 *    - Line   & Circle
 *    - Circle & Circle
 *
 * Для всех остальных требуется выбросить исключение std::logic_error
 */
class IntersectionVisitor {
public:
    std::optional<Point2D> operator()(const Line &lhs, const Line &rhs) const {
        auto p1 = lhs.end - lhs.start;
        auto p2 = rhs.end - rhs.start;

        double det = p1.Cross(p2);

        if (std::abs(det) < 1e-6) {
            return std::nullopt;
        }
        Point2D d3 = rhs.start - lhs.start;
        double t = d3.Cross(p2) / det;
        return Point2D{lhs.start.x + p1.x * t, lhs.start.y + p1.y * t};
    }

    std::pair<std::optional<Point2D>, std::optional<Point2D>> operator()(const Line &lhs, const Circle &rhs) const {
        Point2D d = lhs.end - lhs.start;
        Point2D f = lhs.start - rhs.Center();
        double a = d.Dot(d);
        double b = 2.0 * f.Dot(d);
        double c = f.Dot(f) - rhs.radius * rhs.radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return {std::nullopt, std::nullopt};
        }
        double sqrtDisc = std::sqrt(discriminant);

        double t1 = (-b - sqrtDisc) / (2.0 * a);
        double t2 = (-b + sqrtDisc) / (2.0 * a);
        Point2D intersection1{lhs.start.x + d.x * t1, lhs.start.y + d.y * t1};
        Point2D intersection2{lhs.start.x + d.x * t2, lhs.start.y + d.y * t2};
        if (intersection1 == intersection2) {
            return {intersection1, std::nullopt};
        }
        return {intersection1, intersection2};
    }

    std::pair<std::optional<Point2D>, std::optional<Point2D>> operator()(const Circle &lhs, const Circle &rhs) const {
        double d = lhs.Center().DistanceTo(rhs.Center());

        if (d > lhs.radius + rhs.radius || d < std::abs(lhs.radius - rhs.radius) || d < 1e-10) {
            return {std::nullopt, std::nullopt};
        }

        double a = (d * d + lhs.radius * lhs.radius - rhs.radius * rhs.radius) / (2.0 * d);

        double h = std::sqrt(lhs.radius * lhs.radius - a * a);

        Point2D direction = (rhs.Center() - lhs.Center()).Normalize();
        Point2D midPoint = lhs.Center() + direction * a;

        Point2D perpendicular{-direction.y, direction.x};

        Point2D intersection1 = midPoint + perpendicular * h;
        Point2D intersection2 = midPoint - perpendicular * h;

        return std::make_pair(intersection1, intersection2);
    }
    template <class T, class U>
    std::optional<Point2D> operator()(T &&lhs, U &&rhs) const {
        throw std::logic_error("invalid types");
    }
};

inline std::optional<Point2D> GetIntersectPoint(const Shape &shape1, const Shape &shape2) { return std::nullopt; }

}  // namespace geometry::intersections