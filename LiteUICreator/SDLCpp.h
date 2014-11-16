#ifndef SDLCPP_H_
#define SDLCPP_H_

// SDL backend renderer for LiteUI

#include <liteui.h>
#include <SDL.h>
#include <string>

typedef SDL_Window* Window;
typedef SDL_Renderer* Renderer;

class RenderContext;

#include <memory>
typedef std::shared_ptr<RenderContext> CRenderContext;

class RenderContext
{
public:
  typedef unsigned char col;

  typedef void (*KeyboardCallback)(int key);
private:

  Window _window;
  Renderer _renderer;
  liteui::scene* _scene;
  KeyboardCallback _cb;

  RenderContext(const RenderContext&){}
  RenderContext& operator=(const RenderContext&){}

  void Render();
public:
  RenderContext(const std::string& name, int width, int height);
  ~RenderContext();

  void SetActiveScene(liteui::scene* pScene) { _scene = pScene; }
  void SetKeyCallback(KeyboardCallback cb){ _cb = cb; }

  int Run();

  void SetRenderDrawColor(col r, col g, col b, col a = 255);
  void RenderRect(int x, int y, int w, int h);
  void RenderFillRect(int x, int y, int w, int h);

  //inline Window Window(){ return _window; }
  //inline Renderer Renderer(){ return _renderer; }
};

#endif
