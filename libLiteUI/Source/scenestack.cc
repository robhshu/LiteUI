//
//  liteui::scenestack
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Mar 2014
//
#include <liteui/scenestack.h>

#include <cassert>

namespace liteui
{
scenestack::scenestack( scenegraph &sg )
  : m_sceneGraph(sg)
{ }

scenestack::~scenestack( )
{ }

void scenestack::PushScene( const string &szName, bool bAllowDuplicate /*= false*/ )
{
  if (!bAllowDuplicate && HasSceneNamed(szName)) {
    return;
  }

  scene *pScene = m_sceneGraph.FindScene(szName);

  if( pScene ) {
    m_sceneStack.push_back( pScene );
  }
}

void scenestack::PopScene( )
{
  m_sceneStack.pop_back();
}

void scenestack::Clear( )
{
  m_sceneStack.clear();
}

void scenestack::Render( )
{
  // this works because the last item is the top-most

  for( sceneptrvecIt i( m_sceneStack.begin() ); i!=m_sceneStack.end(); i++ ) {
    (*i)->RenderScene( );
  }
}

void scenestack::UpdateAll( )
{
  bool bFirst = true;

  for (sceneptrvec::reverse_iterator i(m_sceneStack.rbegin()); i != m_sceneStack.rend(); i++) {

    // xxxx all scenes are updated, not just the top-most. this is an active issue.
    (*i)->UpdateScene();

    bFirst = false;
  }
}

scene &scenestack::Top( ) const
{
  assert(!Empty());

  return *m_sceneStack.back();
}

bool scenestack::IsTop( const string &szName ) const
{
  if( !Empty( ) ) {
    if( Top().GetName() == szName ) {
      return true;
    }
  }

  return false;
}

bool scenestack::Empty( ) const
{
  return m_sceneStack.empty( );
}

bool scenestack::HasSceneNamed(const string &szName) const
{
  for( sceneptrvecCIt ci( m_sceneStack.begin() ); ci!=m_sceneStack.end(); ci++ ) {
    if( (*ci)->GetName() == szName ) {
      return true;
    }
  }

  return false;
}

};
