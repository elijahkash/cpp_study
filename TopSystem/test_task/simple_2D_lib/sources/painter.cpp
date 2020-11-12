#include "painter.hpp"

#include <cmath>

#include "defaults.hpp"

namespace simple_2d_lib {

Painter::Painter()
  : clearColor(DEFAULT_PAINTER_CLEAR_COLOR)
  , penColor(DEFAULT_PAINTER_PEN_COLOR) {

}

void Painter::drawPoint(glm::fvec2 pos) const {
  setPointPixels(normalize(vertexShader(pos)));
}

void Painter::drawLine(glm::fvec2 start, glm::fvec2 end) const {
  setLinePixels(normalize(vertexShader(start)), normalize(vertexShader(end)));
}

void Painter::setClearColor(Color newClearColor) {
  clearColor = newClearColor;
}

void Painter::setPenColor(Color newPenColor) {
  penColor = newPenColor;
}

glm::i32vec2 Painter::normalize(glm::fvec2 coords) {
  // TODO: protect from overflow (from long to int)
  return glm::i32vec2(std::lround(coords.x), std::lround(coords.y));
}

}  // simple_2d_lib
