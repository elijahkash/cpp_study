#include "default_painter.hpp"

#include <utility>

DefaultPainter::DefaultPainter(uint32_t width,
                               uint32_t height,
                               std::shared_ptr<Color[]> buf)
  : width(width)
  , height(height)
  , buf(std::move(buf)) {
}

void DefaultPainter::clear() {
  uint32_t size = width * height;
  for (uint32_t i = 0; i < size; i++)
    buf[i] = clearColor;
}

void DefaultPainter::setPixel(glm::i32vec2 coords) {
  if (coords.x >= 0 and coords.x < width
      and coords.y >= 0 and coords.y < height)
    buf[coords.y * width + coords.x] = penColor;
}

void DefaultPainter::setPointPixels(glm::i32vec2 pos) {
  setPixel(pos);

  setPixel({pos.x + 1, pos.y});
  setPixel({pos.x - 1, pos.y});
  setPixel({pos.x, pos.y + 1});
  setPixel({pos.x, pos.y - 1});

  setPixel({pos.x + 2, pos.y});
  setPixel({pos.x - 2, pos.y});
  setPixel({pos.x, pos.y + 2});
  setPixel({pos.x, pos.y - 2});

  setPixel({pos.x + 1, pos.y + 1});
  setPixel({pos.x + 1, pos.y - 1});
  setPixel({pos.x - 1, pos.y + 1});
  setPixel({pos.x - 1, pos.y - 1});
}

void DefaultPainter::setLinePixels(glm::i32vec2 start, glm::i32vec2 end) {
  const int32_t deltaX = abs(end.x - start.x);
  const int32_t deltaY = abs(end.y - start.y);
  const int32_t signX = start.x < end.x ? 1 : -1;
  const int32_t signY = start.y < end.y ? 1 : -1;
  int32_t error = deltaX - deltaY;
  setPixel({start.y, end.y});
  while(start.x != end.x || start.y != end.y) {
    setPixel({start.x, start.y});
    const int32_t error2 = error * 2;
    if(error2 > -deltaY) {
      error -= deltaY;
      start.x += signX;
    }
    if(error2 < deltaX) {
      error += deltaX;
      start.y += signY;
    }
  }
}
