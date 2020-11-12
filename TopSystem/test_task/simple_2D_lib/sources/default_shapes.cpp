#include "default_shapes.hpp"

namespace simple_2d_lib {

Point::Point(glm::fvec2 point) : point(point) {
}

void Point::draw(Painter *painter) const {
  painter->drawPoint(point);
}

Line::Line(glm::fvec2 point1, glm::fvec2 point2)
  : point1(point1), point2(point2) {
}

void Line::draw(Painter *painter) const {
  painter->drawLine(point1, point2);
}

Triangle::Triangle(glm::fvec2 point1, glm::fvec2 point2, glm::fvec2 point3)
  : point1(point1), point2(point2), point3(point3) {
}

void Triangle::draw(Painter *painter) const {
  painter->drawLine(point1, point2);
  painter->drawLine(point2, point3);
  painter->drawLine(point3, point1);
}

Circle::Circle(glm::fvec2 center, glm::fvec2 radius)
  : center(center), radius(radius) {
}

void Circle::draw(Painter *painter) const {
  painter->drawCircle(center, radius);
}

}  // simple_2d_lib
