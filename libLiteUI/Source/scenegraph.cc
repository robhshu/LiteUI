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
  : m_active( m_sceneList.end() )
{
}

scenegraph::~scenegraph( )
{
  ClearAll();
}

scene &scenegraph::GetActiveScene( )
{
  return *m_active->second;
}

bool scenegraph::NextScene( )
{
  if( m_active == m_sceneList.end() ) {
    return false;
  }

  sceneMap_it next_scene = m_active;
  ++next_scene;

  if( next_scene != m_sceneList.end() ){
    m_active = next_scene;
    return true;
  } else {
    return false;
  }
}

bool scenegraph::PreviousScene( )
{
  if( m_active == m_sceneList.end() || m_active == m_sceneList.begin() ) {
    return false;
  }

  sceneMap_it prev_scene = m_active;
  --prev_scene;

  if( prev_scene != m_sceneList.end() ){
    m_active = prev_scene;
    return true;
  } else {
    return false;
  }
}

void scenegraph::AddScene( scene *pScene, const unsigned uPriority /*= 0*/ )
{
  sceneMap_it pos = m_sceneList.insert( sceneMapPair( uPriority, pScene ) );

  // Default to first added scene
  if( m_active == m_sceneList.end() ) {
    m_active = pos;
  }
}

unsigned scenegraph::CountScenes( ) const
{
  return m_sceneList.size();
}

void scenegraph::ClearAll( )
{
  for( sceneMap_it it=m_sceneList.begin(); it!=m_sceneList.end(); it++ ) {
    (*it).second->Release( );
  }

  m_sceneList.clear();
  m_active = m_sceneList.end();
}

};
