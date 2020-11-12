#include <SDL2/SDL.h>


#include <iostream>
#include <array>

#include "engine.hpp"
#include "default_painter.hpp"

#include "default_shapes/line.hpp"

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

/*class Foo final : public FrameExporter {
 public:
  explicit Foo(SDL_Window* window)
      : window(window), screen_surface(SDL_GetWindowSurface(window)) {}

  void imageExportEvent(
      std::unique_ptr<const PoolOfSurfaces::ExportingSurface> surf) final {

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        (void*)surf->data().data(), SCREEN_WIDTH, SCREEN_HEIGHT,
        24, 3 * SCREEN_WIDTH, rmask, gmask, bmask, 0);

    if (surface == nullptr) {
      std::cout << "Creating surface failed!";
      exit(1);
    }

    SDL_BlitSurface(surface, nullptr, screen_surface, nullptr);

    SDL_UpdateWindowSurface(window);
    static int counter = 0;
    // frames count
    // if (counter++ % 50 == 0)
    //   std::cout << counter << '\n';
    // SDL_Delay(20);
  }

 private:
  SDL_Window* window;
  SDL_Surface* screen_surface;
};*/

int main (int argc, char** argv) {
  // TODO: not every!
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Init fail!\n";
    return 1;
  }

  // SDL_Surface* screen_surface = nullptr;
  SDL_Window* window = nullptr;

  window = SDL_CreateWindow("Hello, SDL 2!", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Window create fail!\n";
    return 1;
  }
  SDL_UpdateWindowSurface(window);

  std::shared_ptr<Color[]> buf(new Color[SCREEN_WIDTH * SCREEN_HEIGHT]);
  DefaultPainter painter(SCREEN_WIDTH, SCREEN_HEIGHT, buf);
  Engine engine(&painter);

  std::array<glm::fvec2, 2> test{};
  test[0] = {10, 10};
  test[0] = {50, 50};

  engine.addShape(std::make_unique<Line>(test[0], test[1]));



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
            engine.camera.move({-1, 0});
            break;
          case 79:  // right
            engine.camera.move({1, 0});
            break;
          case 81:  // down
            engine.camera.move({0, -1});
            break;
          case 82:  // up
            engine.camera.move({0, 1});
            break;

          case 20:  // Q
            engine.camera.rotate(1);
            break;
          case 8:  // E
            engine.camera.rotate(-1);
            break;
        }
      }

      engine.drawFrame();

      SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
          (void*)buf.get(), SCREEN_WIDTH, SCREEN_HEIGHT,
          24, 3 * SCREEN_WIDTH, rmask, gmask, bmask, 0);

      if (surface == nullptr) {
        std::cout << "Creating surface failed!";
        exit(1);
      }

      SDL_BlitSurface(surface, nullptr, SDL_GetWindowSurface(window), nullptr);

      SDL_UpdateWindowSurface(window);

    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}