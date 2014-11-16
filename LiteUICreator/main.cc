#include <Windows.h>

#include "SDLCpp.h"

#include <liteui.h>
#include <fstream>
#include <sstream>

class LiteButton : public liteui::button
{
  CRenderContext _context;
public:
  LiteButton(CRenderContext context) : _context(context){}

  virtual void Render()
  {
    int x = static_cast<int>(GetAbsoluteX() * 800);
    int y = static_cast<int>(GetAbsoluteY() * 600);
        
    _context->SetRenderDrawColor(255, 0, 0);

    _context->RenderFillRect(x, y, GetWidthInScene(800), GetHeightInScene(600));

    // debug:
    _context->SetRenderDrawColor(255, 255, 255);
    _context->RenderRect(x, y, GetWidthInScene(800)-1, GetHeightInScene(600)-1);
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

    // debug overlay:
    int x = static_cast<int>(GetAbsoluteX() * 800);
    int y = static_cast<int>(GetAbsoluteY() * 600);

    _context->SetRenderDrawColor(255, 255, 255);
    _context->RenderRect(x - 1, y - 1, GetWidthInScene(800)+1, GetHeightInScene(600) +1);
  }
};

class LiteSDLParser : public liteui::parser
{
  CRenderContext _context;
public:
  LiteSDLParser(CRenderContext context) : _context(context){}

  virtual liteui::element *OnCreateElement(const std::string &szType)
  {
    if (szType == "button")
    {
      LiteButton *btn(new LiteButton(_context));
      btn->IncReferenceCount();
      return btn;
    }
    else if (szType == "group")
    {
      LiteGroup* group(new LiteGroup(_context));
      group->IncReferenceCount();
      return group;
    }

    return liteui::parser::OnCreateElement(szType);
  }
};

class Playground
{
  CRenderContext _context;

  static liteui::scenegraph sg;
  static CRenderContext m_psSharedContext;

public:

  Playground(int width, int height)
    : _context(new RenderContext("LiteUI Playground", width, height))
  {
    m_psSharedContext = _context;
    m_psSharedContext->SetKeyCallback(Reload);
  }

  int operator()(void)
  {
    Reload(0);
    return _context->Run();
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

    sg.ClearAll();

    LiteSDLParser parser(m_psSharedContext);
    parser.LoadSceneGraph(sg, data);

    if (liteui::scene* scene = sg.FindScene("main")) {

      scene->UpdateScene(false); // horrible
      scene->SetVirtualDimensions(800, 600); // testing

      m_psSharedContext->SetActiveScene(scene);
    }

  }
};

liteui::scenegraph Playground::sg;
CRenderContext Playground::m_psSharedContext(nullptr);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  return Playground(800, 600)();
}
