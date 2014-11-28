#include <Windows.h>

#include "SDLCpp.h"

#include <liteui.h>
#include <fstream>
#include <sstream>

#include <cassert>

class LiteLabel :public liteui::label
{
  CRenderContext _context;
public:
  LiteLabel(CRenderContext context) : _context(context){}

  virtual void Render()
  {
    int x = static_cast<int>(GetAbsoluteX() * 800);
    int y = static_cast<int>(GetAbsoluteY() * 600);

    RenderContext::col shade = IsSelected() ? 128 : 255;
    _context->SetRenderDrawColor(shade, IsHighlighted() ? shade : 0, 0);

    _context->RenderFillRect(x, y, GetWidthInScene(800), GetHeightInScene(600));

#ifdef _DEBUG
    _context->SetRenderDrawColor(255, 255, 255);
    _context->RenderRect(x, y, GetWidthInScene(800) - 1, GetHeightInScene(600) - 1);
#endif
  }
};

class LiteButton : public liteui::button
{
  CRenderContext _context;
public:
  LiteButton(CRenderContext context) : _context(context){}

  virtual void Render()
  {
    int x = static_cast<int>(GetAbsoluteX() * 800);
    int y = static_cast<int>(GetAbsoluteY() * 600);
        
    RenderContext::col shade = IsSelected() ? 128 : 255;
    _context->SetRenderDrawColor(shade, 0, IsHighlighted() ? shade : 0);

    _context->RenderFillRect(x, y, GetWidthInScene(800), GetHeightInScene(600));

#ifdef _DEBUG
    _context->SetRenderDrawColor(255, 255, 255);
    _context->RenderRect(x, y, GetWidthInScene(800)-1, GetHeightInScene(600)-1);
#endif
  }
};

class LiteGroup: public liteui::group
{
  CRenderContext _context;
public:
  LiteGroup(CRenderContext context) : _context(context){}

  virtual void Render()
  {
    liteui::group::Render();

#ifdef _DEBUG
    int x = static_cast<int>(GetAbsoluteX() * 800);
    int y = static_cast<int>(GetAbsoluteY() * 600);

    _context->SetRenderDrawColor(255, 255, 255);
    _context->RenderRect(x - 1, y - 1, GetWidthInScene(800)+1, GetHeightInScene(600) +1);
#endif
  }
};

class LiteSDLParser : public liteui::parser
{
  CRenderContext _context;
public:
  LiteSDLParser(CRenderContext context) : _context(context){}

  virtual liteui::element *OnCreateElement(const std::string &szType)
  {
#define CREATE_ELEMENT(type) \
  type* ele(new type(_context)); \
  assert(ele->GetTypeName() == szType); \
  return ele;

    if (szType == "button") {
      CREATE_ELEMENT(LiteButton);
    } else if (szType == "label") {
      CREATE_ELEMENT(LiteLabel);
    } else if (szType == "group") {
      CREATE_ELEMENT(LiteGroup);
    }

    return liteui::parser::OnCreateElement(szType);
  }
};

class Playground
{
  CRenderContext _context;

  static liteui::scenegraph sg;
  static liteui::scenestack ss;
  static CRenderContext m_psSharedContext;

public:

  Playground(int width, int height)
    : _context(new RenderContext("LiteUI Playground", width, height))
  {
    m_psSharedContext = _context;
    m_psSharedContext->SetKeyCallback(Reload);
    m_psSharedContext->SetCursorCalback(MoveCursor);
  }

  int operator()(void)
  {
    Reload(0);
    return _context->Run();
  }

  static void MoveCursor(int x, int y, int button)
  {
    if (m_psSharedContext && m_psSharedContext->Scene())
    {
      m_psSharedContext->Scene()->SetCursor(liteui::n_unit(x) / 800, liteui::n_unit(y) / 600, button == 1);
      m_psSharedContext->Scene()->UpdateScene(true);
    }
  }

  static void Reload(int method)
  {
    std::string data;

    std::ifstream txt("testxml.xml");
    if (txt.is_open()) {
      std::string line;
      while (std::getline(txt, line)) {
        data += line;
      }
    }

    if (data.empty()) {
      return;
    }

    ss.Clear();
    sg.ClearAll();

    LiteSDLParser parser(m_psSharedContext);
    parser.LoadSceneGraph(sg, data);

    ss.PushScene("main");

    if (!ss.Empty() ) {

      liteui::scene& scene(ss.Top());

      scene.UpdateScene(false);
      scene.SetVirtualDimensions(800, 600); // testing

      m_psSharedContext->SetActiveScene(&scene);
    }

  }
};

liteui::scenegraph Playground::sg;
liteui::scenestack Playground::ss(Playground::sg);
CRenderContext Playground::m_psSharedContext(nullptr);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  return Playground(800, 600)();
}
