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
  : m_idx( 0 )
{
}

scenegraph::~scenegraph( )
{
  for( scenes_it it=m_sceneList.begin(); it!=m_sceneList.end(); it++ ) {
    (*it)->Release( );
  }

  m_sceneList.clear();
}

scene &scenegraph::GetActiveScene( )
{
  return *m_sceneList[m_idx];
}

bool scenegraph::NextScene( )
{
  if( m_idx < m_sceneList.size() -1 ) {
    m_idx++;
    return true;
  } else {
    return false;
  }
}

bool scenegraph::PreviousScene( )
{
  if( m_idx > 0 ) {
    m_idx--;
    return true;
  } else {
    return false;
  }
}

void scenegraph::AddScene( scene *pScene )
{
  m_sceneList.push_back( pScene );
}

};
