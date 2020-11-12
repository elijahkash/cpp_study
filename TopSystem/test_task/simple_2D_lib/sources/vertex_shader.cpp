#include "vertex_shader.hpp"

VertexShader::VertexShader() : viewMatrix(1.0) {
}

glm::fvec2 VertexShader::operator()(glm::fvec2 vertex) {
  return glm::fvec3(vertex, 1) * viewMatrix;
}

void VertexShader::setViewMatrix(glm::fmat3 newViewMatrix) {
  viewMatrix = newViewMatrix;
}
