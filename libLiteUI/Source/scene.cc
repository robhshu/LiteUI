//
//  liteui::scene
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/scene.h>
#include <algorithm>

namespace liteui
{

scene::scene( )
  : base("scene")
  , m_lastMsg( 0, 0, 0 )
{
}

scene::~scene( )
{
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Release();
  }

  m_groupItems.clear();
}

void scene::AddGroup( group *pGroup )
{
  if( !HasGroup( pGroup ) ) {
    m_groupItems.push_back( pGroup );
    Dirty();
  }
}

void scene::RenderScene( )
{
  if( m_bDirty ) {
    UpdateScene();
  }
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Render();
  }
}

void scene::UpdateScene( )
{
  if( m_bDirty ) {
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->OnMessage(m_lastMsg);
    }
    
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->Update();
    }
    
    m_bDirty = false;
  }
}

bool scene::HasGroup( group *pGroup ) const
{
  return find(m_groupItems.begin(), m_groupItems.end(), pGroup ) != m_groupItems.end();
}

void scene::SetCursor( unsigned px, unsigned py, bool bPressed )
{
  if( m_bDirty || px != m_lastMsg.GetCursorX() || py != m_lastMsg.GetCursorY() || bPressed != m_lastMsg.HasPointerHeld() )
  {
    Dirty();
    m_lastMsg.Set( px, py, bPressed );
  }
}

};
