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
  int x = 0;
  int y = radius.length();
  int delta = 1 - 2 * radius;
  int error = 0;
  while(y >= 0) {
    setPixel(x0 + x, y0 + y);
    setPixel(x0 + x, y0 - y);
    setPixel(x0 - x, y0 + y);
    setPixel(x0 - x, y0 - y);
    error = 2 * (delta + y) - 1;
    if(delta < 0 && error <= 0) {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
    error = 2 * (delta - x) - 1;
    if(delta > 0 && error > 0) {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

}  // simple_2d_lib
