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
}

scene &scenegraph::GetActiveScene( )
{
  return *m_sceneList.front();
}

void scenegraph::AddScene( scene *pScene )
{
  m_sceneList.push_back( pScene );
}

};
