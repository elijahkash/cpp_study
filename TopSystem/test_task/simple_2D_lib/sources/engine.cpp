#include "engine.hpp"

#include <utility>

Engine::Engine(Painter *painter)
 : painter(painter) {
}

void Engine::drawFrame() {
  painter->clear();
  for (const auto& item : items)
    item->draw(painter);
}

void Engine::addShape(std::unique_ptr<Shape> newShape) {
  items.emplace_back(std::move(newShape));
}
