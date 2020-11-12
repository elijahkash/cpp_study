#include "painter.hpp"

#include <cmath>

#include "defaults.hpp"

namespace simple_2d_lib {

glm::i32vec2 normalize(glm::fvec2 coords) {
  // TODO: protect from overflow (from long to int)
  return glm::i32vec2(std::lround(coords.x), std::lround(coords.y));
}

PaintEngine::PaintEngine()
    : clearColor(DEFAULT_PAINTER_CLEAR_COLOR)
    , penColor(DEFAULT_PAINTER_PEN_COLOR) {
}

void PaintEngine::setClearColor(Color newClearColor) {
  clearColor = newClearColor;
}

void PaintEngine::setPenColor(Color newPenColor) {
  penColor = newPenColor;
}

void Painter::drawPoint(glm::fvec2 pos) const {
  setPointPixels(normalize(vertexShader(pos)));
}

void Painter::drawLine(glm::fvec2 start, glm::fvec2 end) const {
  setLinePixels(normalize(vertexShader(start)), normalize(vertexShader(end)));
}

void Painter::drawCircle(glm::fvec2 center, glm::fvec2 radius) const {
  glm::fvec2 modCenter = vertexShader(center);
  // TODO: protect from overflow (from long to int)
  setCirclePixels(normalize(modCenter),
                  std::lround(glm::length(modCenter - vertexShader(radius))));
}

}  // simple_2d_lib
