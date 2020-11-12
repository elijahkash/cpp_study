#include "vertex_shader.hpp"

namespace simple_2d_lib {

VertexShader::VertexShader() : viewMatrix(1.0) {
}

glm::fvec2 VertexShader::operator()(glm::fvec2 vertex) const noexcept {
  return viewMatrix * glm::fvec3(vertex, 1);
}

void VertexShader::setViewMatrix(glm::fmat3 newViewMatrix) noexcept {
  viewMatrix = newViewMatrix;
}

}  // simple_2d_lib
