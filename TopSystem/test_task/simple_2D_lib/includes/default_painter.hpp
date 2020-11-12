#ifndef TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_
#define TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_

#include <memory>

#include "painter.hpp"
#include "color.hpp"

namespace simple_2d_lib {

class DefaultPainter : public Painter {
 public:
  DefaultPainter(uint32_t width, uint32_t height, std::shared_ptr<Color[]> buf);

  void updateBuf(std::shared_ptr<Color[]> newBuf);

  void setPixel(glm::i32vec2 coords) const override;
  void clear() const override;

 private:
  uint32_t width;
  uint32_t height;

  std::shared_ptr<Color[]> buf;
  void setPointPixels(glm::i32vec2 pos) const override;
  void setLinePixels(glm::i32vec2 start, glm::i32vec2 end) const override;
  void setCirclePixels(glm::i32vec2 center, int32_t radius) const override;
};

}  // simple_2d_lib

#endif // TEST_TASK_SIMPLE_2D_LIB_INCLUDES_DEFAULT_PAINTER_HPP_
