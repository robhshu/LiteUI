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
  , m_lastPx( 0 )
  , m_lastPy( 0 )
{
}
  
void scene::AddGroup( group *pGroup )
{
  if( !HasGroup( pGroup ) ) {
    m_groupItems.push_back( pGroup );
    m_bDirty = true;
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
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Update();
  }

  m_bDirty = false;
}

bool scene::HasGroup( group *pGroup ) const
{
  return find(m_groupItems.begin(), m_groupItems.end(), pGroup ) != m_groupItems.end();
}

void scene::SetCursor( unsigned px, unsigned py )
{
  if( px != m_lastPx || py != m_lastPy || m_bDirty ) {   
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->OnMessage(px, py);
    }

    m_lastPx = px;
    m_lastPy = py;
  }
}

};
