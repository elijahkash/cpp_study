#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_HPP_

#include <iterator>

#include "shape.hpp"

namespace simple_2d_lib {

class Point : public Shape {
 public:
  explicit Point(glm::fvec2 point);

  void draw(Painter *painter) const override;

 protected:
  glm::fvec2 point;
};

class Line : public Shape {
 public:
  Line(glm::fvec2 point1, glm::fvec2 point2);

  void draw(Painter *painter) const override;

 protected:
  glm::fvec2 point1;
  glm::fvec2 point2;
};

class Triangle : public Shape {
 public:
  Triangle(glm::fvec2 point1, glm::fvec2 point2, glm::fvec2 point3);

  void draw(Painter *painter) const override;

 protected:
  glm::fvec2 point1;
  glm::fvec2 point2;
  glm::fvec2 point3;
};

class Circle : public Shape {
 public:
  Circle(glm::fvec2 center, glm::fvec2 radius);

  void draw(Painter *painter) const override;

 protected:
  glm::fvec2 center;
  glm::fvec2 radius;
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_HPP_
