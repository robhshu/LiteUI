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

scenegraph::~scenegraph( )
{
  ClearAll();
}

scene &scenegraph::CreateScene( )
{
  scene *pScene = new scene;
  m_scenes.push_back(pScene);
  return *pScene;
}

void scenegraph::AddScene( scene &ref )
{
  sceneptrvecIt res = find(m_scenes.begin(), m_scenes.end(), &ref);

  // check it does not already exist
  if( res == m_scenes.end() ) {
    m_scenes.push_back(&ref);
  }
}

void scenegraph::DestroyScene( scene &ref )
{
  sceneptrvecIt res = find(m_scenes.begin(), m_scenes.end(), &ref);

  // destroy and remove if it does exist
  if( res != m_scenes.end() ) {
    (*res)->Release();
    m_scenes.erase(res);
  }
}

scene *scenegraph::FindScene( const string &szName )
{
  for( sceneptrvecIt it=m_scenes.begin(); it!=m_scenes.end(); it++ ) {
    if( (*it)->GetName() == szName ) {
      return (*it);
    }
  }

  return nullptr;
}

void scenegraph::ClearAll( )
{
  for( sceneptrvecIt it=m_scenes.begin(); it!=m_scenes.end(); it++ ) {
    (*it)->Release();
  }

  m_scenes.clear();
}

};
