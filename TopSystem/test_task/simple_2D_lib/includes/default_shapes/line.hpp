#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_LINE_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_LINE_HPP_

#include <iterator>

#include "shape.hpp"

class Line : public ShapeLinearStorage<2> {
 public:
  // template<typename Iterator>
  // Line(Iterator begin, Iterator end);

  Line(glm::fvec2 point1, glm::fvec2 point2);

  void draw(Painter *painter) const override;
};

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_SHAPES_LINE_HPP_
