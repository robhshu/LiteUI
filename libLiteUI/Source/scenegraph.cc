//
//  liteui::scenegraph
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/scenegraph.h>

namespace liteui
{
scenegraph::scenegraph( )
{
  m_sceneList.resize(1);
}

scene &scenegraph::GetRootScene( )
{
  return m_sceneList.front();
}

};
