#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_

#include "painter.hpp"

namespace simple_2d_lib {

// TODO: constructors?
class Shape {
 public:
  virtual void draw(Painter* painter) const = 0;
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_SHAPE_HPP_
