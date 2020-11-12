#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_

#include <glm/glm.hpp>

#include "color.hpp"
#include "vertex_shader.hpp"

namespace simple_2d_lib {

static glm::i32vec2 normalize(glm::fvec2 coords);

class PaintEngine {
 public:
  PaintEngine();

  virtual void setPixel(glm::i32vec2 coords) const = 0;
  virtual void clear() const = 0;

  void setClearColor(Color newClearColor);
  void setPenColor(Color newPenColor);

 protected:
  Color clearColor;
  Color penColor;
};

class Painter : public PaintEngine {
 public: // methods
  Painter() = default;

  void drawPoint(glm::fvec2 pos) const;
  void drawLine(glm::fvec2 start, glm::fvec2 end) const;
  void drawCircle(glm::fvec2 center, glm::fvec2 radius) const;


 public: // properties
  VertexShader vertexShader;

 protected:

  virtual void setPointPixels(glm::i32vec2 pos) const = 0;
  virtual void setLinePixels(glm::i32vec2 start, glm::i32vec2 end) const = 0;
  virtual void setCirclePixels(glm::i32vec2 center, int32_t radius) const = 0;
};

}  // simple_2d_lib

#endif  // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_PAINTER_HPP_
