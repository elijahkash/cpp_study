#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_CAMERA_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_CAMERA_HPP_

#include <glm/glm.hpp>

// TODO: protect from integers overflow!
class Camera2D {
 public:
  Camera2D();
  ~Camera2D() = default;

  void setPos(glm::fvec2 newPos) noexcept;
  // TODO: negative scale?
  void setScale(float newScale) noexcept;
  void setRoll(float newRoll) noexcept;

  void move(glm::fvec2 biasPos) noexcept;
  void rotate(float biasRoll) noexcept;


  [[nodiscard]] glm::fvec2 getPos() const noexcept;
  [[nodiscard]] float getScale() const noexcept;
  [[nodiscard]] float getRoll() const noexcept;

  [[nodiscard]] glm::fmat3 getViewMatrix() const noexcept;

 private:
  glm::fvec2 pos;
  float scale;
  // degrees
  float roll;
};

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_CAMERA_HPP_
