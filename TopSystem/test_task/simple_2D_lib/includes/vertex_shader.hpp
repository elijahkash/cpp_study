#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_

#include <glm/glm.hpp>

namespace simple_2d_lib {

// TODO: implement  modelMatrix
class VertexShader {
 public:
  VertexShader();

  glm::fvec2 operator ()(glm::fvec2 vertex) const noexcept;

  void setViewMatrix(glm::fmat3 newViewMatrix) noexcept;

 private:
  glm::fmat3 viewMatrix;
  // if more than one matrix add resultMatrix!
  // glm::fmat3 resultMatrix;
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_
