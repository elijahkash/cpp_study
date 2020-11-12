#include "camera.hpp"

#include <cmath>  // fmod

#include <glm/gtx/matrix_transform_2d.hpp>

#include "defaults.hpp"

namespace simple_2d_lib {

Camera2D::Camera2D()
  : pos(DEFAULT_CAMERA_X, DEFAULT_CAMERA_Y)
  , scale(DEFAULT_CAMERA_SCALE)
  , roll(DEFAULT_CAMERA_ROLL) {
}

void Camera2D::setPos(glm::fvec2 newPos) noexcept {
  pos = newPos;
}

void Camera2D::setScale(float newScale) noexcept {
  scale = newScale;
}

void Camera2D::setRoll(float newRoll) noexcept {
  roll = newRoll;
  roll = std::fmod(roll, 360);
}

void Camera2D::move(glm::fvec2 biasPos) noexcept {
  pos += biasPos;
}

void Camera2D::rotate(float biasRoll) noexcept {
  roll += biasRoll;
  roll = std::fmod(roll, 360);
}

glm::fvec2 Camera2D::getPos() const noexcept {
  return pos;
}

float Camera2D::getScale() const noexcept {
  return scale;
}

float Camera2D::getRoll() const noexcept {
  return roll;
}

glm::fmat3 Camera2D::getViewMatrix() const noexcept {
  glm::fmat3 viewMatrix(1.0);
  viewMatrix = glm::translate(viewMatrix, pos);
  viewMatrix = glm::scale(viewMatrix, glm::fvec2(scale));
  viewMatrix = glm::rotate(viewMatrix, glm::radians<float>(roll));
  return viewMatrix;
}

}  // simple_2d_lib
