#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_

#include <glm/glm.hpp>

#include "color.hpp"
#include "vertex_shader.hpp"

class Painter {
 public: // methods
  Painter();

  void drawPoint(glm::fvec2 pos);
  void drawLine(glm::fvec2 start, glm::fvec2 end);
  virtual void clear() = 0;  // TODO: is it right, that painter clear frame?

  void setClearColor(Color newClearColor);
  void setPenColor(Color newPenColor);

 public: // properties
  VertexShader vertexShader;

 protected:
  Color clearColor;
  Color penColor;

  virtual void setPixel(glm::i32vec2 coords) = 0;
  virtual void setPointPixels(glm::i32vec2 pos) = 0;
  virtual void setLinePixels(glm::i32vec2 start, glm::i32vec2 end) = 0;

 private:
  // TODO: static? remove from class?
  static glm::i32vec2 normalize(glm::fvec2 coords);
};

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
