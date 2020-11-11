#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_

#include <cstdint>
#include <memory>

// TODO: need?
#include <glm/glm.hpp>

#include "camera.hpp"

namespace simple_2d_lib {

class Engine {
 public:  // methods
  Engine();
  ~Engine() = default;

  // TODO: do i need to implement this?
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;

  void drawFrame(uint32_t width, uint32_t height,
                 std::shared_ptr<uint32_t> buffer);

 public:  // properties
  Camera2D camera;

 private: // properties

};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_ENGINE_HPP_
