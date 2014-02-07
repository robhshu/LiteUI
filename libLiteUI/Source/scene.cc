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
  
void scene::AddGroup( group *pGroup )
{
  if( !HasGroup( pGroup ) ) {
    m_groupItems.push_back( pGroup );
    Dirty();
  }
}

group *scene::FindGroupNyName( const char* cGroupName )
{
  // todo: implement

  return nullptr;
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

void scene::SetCursor( unsigned px, unsigned py, unsigned mstate )
{
  if( m_bDirty || px != m_lastMsg.GetCursorX() || py != m_lastMsg.GetCursorY() || mstate != m_lastMsg.GetCursorState() )
  {
    Dirty();
    m_lastMsg.Set( px, py, mstate );
  }
}

};
