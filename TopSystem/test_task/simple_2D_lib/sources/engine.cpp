#include "engine.hpp"

namespace simple_2d_lib {

Engine::Engine(Painter *painter)
    : painter(painter) {
}

void Engine::drawFrame() {
  painter->clear();
  painter->vertexShader.setViewMatrix(camera.getViewMatrix());
  for (const auto& item : items)
    item->draw(painter);
}

}  // simple_2d_lib
