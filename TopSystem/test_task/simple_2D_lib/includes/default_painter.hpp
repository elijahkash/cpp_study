#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_

#include <memory>

#include "painter.hpp"
#include "color.hpp"

class DefaultPainter : public Painter {
 public:
  DefaultPainter(uint32_t width, uint32_t height, std::shared_ptr<Color[]> buf);

  void clear() override;

 private:
  uint32_t width;
  uint32_t height;
  std::shared_ptr<Color[]> buf;

  void setPixel(glm::i32vec2 coords) override;
  void setPointPixels(glm::i32vec2 pos) override;
  void setLinePixels(glm::i32vec2 start, glm::i32vec2 end) override;
};

#endif // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_
