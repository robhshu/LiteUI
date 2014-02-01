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
{
}
  
void scene::AddGroup( group *pGroup )
{
  if( !HasGroup( pGroup ) ) {
    m_groupItems.push_back( pGroup );
  }
}

group *scene::FindGroupNyName( const char* cGroupName )
{
  // todo: implement

  return nullptr;
}

void scene::RenderScene( )
{
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Render();
  }
}

bool scene::HasGroup( group *pGroup ) const
{
  return find(m_groupItems.begin(), m_groupItems.end(), pGroup ) != m_groupItems.end();
}

};
