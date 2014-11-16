#include "SDLCpp.h"

RenderContext::RenderContext(const std::string& name, int width, int height)
  : _window(nullptr)
  , _renderer(nullptr)
  , _scene(nullptr)
  , _cb(nullptr)
  , _cbCursor(nullptr)
{
  _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

  if (_window) {
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  }
}

RenderContext::~RenderContext()
{
  if (_renderer) {
    SDL_DestroyRenderer(_renderer);
  }
  if (_window) {
    SDL_DestroyWindow(_window);
  }
}

void RenderContext::SetRenderDrawColor(col r, col g, col b, col a)
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void RenderContext::RenderRect(int x, int y, int w, int h)
{
  SDL_Rect r = { x, y, w, h };
  SDL_RenderDrawRect(_renderer, &r);
}

void RenderContext::RenderFillRect(int x, int y, int w, int h)
{
  SDL_Rect r = { x, y, w, h };
  SDL_RenderFillRect(_renderer, &r);
}

void RenderContext::Render()
{
  SetRenderDrawColor(0, 0, 0);
  SDL_RenderClear(_renderer);

  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

  if (_scene) {
    _scene->RenderScene();
  }

  SDL_RenderPresent(_renderer);
}

int RenderContext::Run()
{
  if (!_renderer) {
    return 0;
  }

  bool bQuit = false;

  while (!bQuit)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          bQuit = true;
          break;
        case SDL_KEYDOWN:
          if (_cb && e.key.keysym.scancode == SDL_SCANCODE_F5){
            _cb(1);
          }
          break;
        case SDL_MOUSEMOTION:
          if (_cbCursor) {
            _cbCursor(e.motion.x, e.motion.y, 0);
          }
          break;
      }
    }

    // todo: run update loop?

    Render();
  }

  return 1;
}
