#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_

#include <array>

#include <glm/glm.hpp>

#include "painter.hpp"

// TODO: constructors?
class Shape {
 public:
  virtual void draw(Painter* painter) const = 0;
};

template<int vertexCount>
class ShapeLinearStorage : public Shape {
  // TODO: check iterator requirements
  // template<typename Iterator>
  // ShapeLinearStorage(Iterator begin, Iterator end);

 protected:
  std::array<glm::fvec2, vertexCount>  vertices;
};

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_
