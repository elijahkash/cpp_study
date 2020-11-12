#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_

#include <glm/glm.hpp>

// TODO: implement  modelMatrix
class VertexShader {
 public:
  VertexShader();

  glm::fvec2 operator ()(glm::fvec2 vertex);

  void setViewMatrix(glm::fmat3 newViewMatrix);

 private:
  glm::fmat3 viewMatrix;
  // if more than one matrix add resultMatrix!
  // glm::fmat3 resultMatrix;
};

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_VERTEX_SHADER_HPP_
