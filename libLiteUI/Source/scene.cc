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
  , bound_w( 1.0f )
  , bound_h( 1.0f )
{
}

scene::~scene( )
{
  m_groupItems.clear();
}

void scene::Dirty( bool bAll /* = false */ )
{
  if( bAll ) {
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->Dirty(true);
    }
  }

  MarkDirty();
}

void scene::AddGroup(group::ptr pGroup)
{
  if( !HasGroup( pGroup.get() ) ) {
    m_groupItems.push_back( pGroup );
    Dirty(false);
  }
}

void scene::RenderScene( )
{
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Render();
  }
}

void scene::UpdateScene( )
{
  // Messages can be sent without marking anything dirty

  if (m_lastMsg.IsNew()) {
    for (groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++) {
      (*it)->OnMessage(m_lastMsg);
    }

    m_lastMsg.Clear();
  }

  // If the dirty flag was set, or if the message has updated something

  if( m_bDirty ) {
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->Update();
    }
    
    m_bDirty = false;
  }
}

bool scene::HasGroup( group *pGroup ) const
{
  groups_cit groupsCIt(m_groupItems.begin());
  while (groupsCIt != m_groupItems.end()){
    if ((*groupsCIt).get() == pGroup) {
      return true;
    }

    ++groupsCIt;
  }
  
  return false;
}

void scene::SetCursor( n_unit px, n_unit py, bool bPressed )
{
  if( m_bDirty || px != m_lastMsg.GetCursorX() || py != m_lastMsg.GetCursorY() || bPressed != m_lastMsg.HasPointerHeld() )
  {
    // This sets the new flag on the message
    m_lastMsg.Set( px, py, bPressed );
  }
}

element *scene::FindChildByName( const string &szName )
{
  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    if( (*it)->HasCustomName() && (*it)->GetName() == szName ) {
      return (*it).get();
    }

    element::ptr elementinst = (*it)->FindChildByName(szName);
    if (elementinst != nullptr) {
      return elementinst.get();
    }
  }

  return nullptr;
}

void scene::SetVirtualDimensions(n_unit width, n_unit height)
{
  bound_w = width;
  bound_h = height;
}

bool scene::GetObjectUserData( const string &szName, unsigned &user_data )
{
  const element *pElement = FindChildByName( szName );
  if( pElement != nullptr ) {
    user_data = pElement->GetUserData();
    return true;
  } else {
    return false;
  }
}

bool scene::SetObjectUserData( const string &szName, const unsigned user_data )
{
  element *pElement = FindChildByName( szName );
  if( pElement != nullptr ) {
    pElement->SetUserData(user_data);
    return true;
  } else {
    return false;
  }
}

};
