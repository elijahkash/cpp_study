#include "default_shapes/line.hpp"

// template<typename Iterator>
// Line::Line(Iterator begin, Iterator end) : ShapeLinearStorage(begin, end) {
// }

Line::Line(glm::fvec2 point1, glm::fvec2 point2) {
  vertices[0] = point1;
  vertices[1] = point2;
}

void Line::draw(Painter *painter) const {
  painter->drawLine(vertices[0], vertices[1]);
}
