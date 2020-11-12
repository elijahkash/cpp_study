#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_

#include <glm/glm.hpp>

#include "color.hpp"
#include "vertex_shader.hpp"

namespace simple_2d_lib {

class Painter {
 public: // methods
  Painter();

  void drawPoint(glm::fvec2 pos) const;
  void drawLine(glm::fvec2 start, glm::fvec2 end) const;
  virtual void clear() const = 0;

  void setClearColor(Color newClearColor);
  void setPenColor(Color newPenColor);

 public: // properties
  VertexShader vertexShader;

 protected:
  Color clearColor;
  Color penColor;

  virtual void setPixel(glm::i32vec2 coords) const = 0;
  virtual void setPointPixels(glm::i32vec2 pos) const = 0;
  virtual void setLinePixels(glm::i32vec2 start, glm::i32vec2 end) const = 0;

 private:
  // TODO: remove from class?
  static glm::i32vec2 normalize(glm::fvec2 coords);
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
