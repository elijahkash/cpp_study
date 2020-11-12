#include <SDL2/SDL.h>

#include <iostream>

#include "engine.hpp"
#include "default_painter.hpp"
#include "default_shapes.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
int shift = (req_format == STBI_rgb) ? 8 : 0;
  rmask = 0xff000000 >> shift;
  gmask = 0x00ff0000 >> shift;
  bmask = 0x0000ff00 >> shift;
#else // little endian, like x86
  unsigned rmask = 0x000000ff;
  unsigned gmask = 0x0000ff00;
  unsigned bmask = 0x00ff0000;
#endif

std::vector<std::unique_ptr<simple_2d_lib::Shape>> createItems() {
  std::vector<std::unique_ptr<simple_2d_lib::Shape>> res;

  glm::fvec2 point1;
  glm::fvec2 point2;
  glm::fvec2 point3;

  point1 = {0, 0};
  point2 = {50, 50};
  point3 = {-50, -50};
  res.emplace_back(std::make_unique<simple_2d_lib::Point>(point1));
  res.emplace_back(std::make_unique<simple_2d_lib::Point>(point2));
  res.emplace_back(std::make_unique<simple_2d_lib::Point>(point3));

  point1 = {-100, 0};
  point2 = {100, 0};
  res.emplace_back(std::make_unique<simple_2d_lib::Line>(point1, point2));

  point1 = {0, -100};
  point2 = {0, 100};
  res.emplace_back(std::make_unique<simple_2d_lib::Line>(point1, point2));

  point1 = {-70, 10};
  point2 = {-20, 150};
  res.emplace_back(std::make_unique<simple_2d_lib::Line>(point1, point2));

  point1 = {50, -20};
  point2 = {20, -75};
  point3 = {80, -75};
  res.emplace_back(std::make_unique<simple_2d_lib::Triangle>(
      point1, point2, point3));

  return std::move(res);
}

int main (int argc, char** argv) {
  // TODO: not every!
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Init fail!\n";
    return 1;
  }

  // SDL_Surface* screen_surface = nullptr;
  SDL_Window* window = nullptr;

  window = SDL_CreateWindow("DEMO_APP", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Window create fail!\n";
    return 1;
  }
  SDL_UpdateWindowSurface(window);

  std::shared_ptr<Color[]> buf1(new Color[SCREEN_WIDTH * SCREEN_HEIGHT]);
  std::shared_ptr<Color[]> buf2(new Color[SCREEN_WIDTH * SCREEN_HEIGHT]);

  simple_2d_lib::DefaultPainter painter(SCREEN_WIDTH, SCREEN_HEIGHT, buf1);
  simple_2d_lib::Engine engine(&painter);

  engine.items = createItems();

  engine.drawFrame();

  SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
      (void*)buf1.get(), SCREEN_WIDTH, SCREEN_HEIGHT,
      24, 3 * SCREEN_WIDTH, rmask, gmask, bmask, 0);
  SDL_BlitSurface(surface, nullptr, SDL_GetWindowSurface(window), nullptr);
  SDL_UpdateWindowSurface(window);

  painter.updateBuf(buf2);
  int i = 2;

  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        // std::cout << e.key.keysym.scancode << ' ' <<
        // SDL_GetKeyName(e.key.keysym.sym) << std::endl;
        switch (e.key.keysym.scancode) {
          case 80:  // left
            engine.camera.move({-20, 0});
            break;
          case 79:  // right
            engine.camera.move({20, 0});
            break;
          case 81:  // down
            engine.camera.move({0, -20});
            break;
          case 82:  // up
            engine.camera.move({0, 20});
            break;

          case 22:  // S
            engine.camera.setScale(engine.camera.getScale() - 1);
            break;
          case 26:  // W
            engine.camera.setScale(engine.camera.getScale() + 1);
            break;
          case 20:  // Q
            engine.camera.rotate(1);
            break;
          case 8:  // E
            engine.camera.rotate(-1);
            break;
        }

        engine.drawFrame();

        if (i == 2) {
          surface = SDL_CreateRGBSurfaceFrom(
              (void *) buf2.get(), SCREEN_WIDTH, SCREEN_HEIGHT,
              24, 3 * SCREEN_WIDTH, rmask, gmask, bmask, 0);
          i = 1;
        } else {
          surface = SDL_CreateRGBSurfaceFrom(
              (void *) buf1.get(), SCREEN_WIDTH, SCREEN_HEIGHT,
              24, 3 * SCREEN_WIDTH, rmask, gmask, bmask, 0);
          i = 2;
        }

        if (surface == nullptr) {
          std::cout << "Creating surface failed!";
          exit(1);
        }

        SDL_BlitSurface(surface, nullptr,
                        SDL_GetWindowSurface(window), nullptr);
        SDL_UpdateWindowSurface(window);

        if (i == 1)
          painter.updateBuf(buf1);
        else
          painter.updateBuf(buf2);
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}