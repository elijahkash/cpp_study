#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_

#include <cstdint>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "painter.hpp"
#include "shape.hpp"

namespace simple_2d_lib {

class Engine {
 public:  // methods
  explicit Engine(Painter* painter);
  ~Engine() = default;

  // TODO: do i need to implement this?
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;

  void drawFrame();

 public:  // properties
  Camera2D camera;
  std::vector<std::unique_ptr<Shape>> items;

 private:
  Painter* painter;
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_
