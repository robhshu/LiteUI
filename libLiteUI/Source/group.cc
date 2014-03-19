//
//  liteui::group
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/group.h>
#include <algorithm>

namespace liteui
{

group::group( )
  : element( "group" )
{
}

group::~group( )
{
  for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
    (*it)->Release();
  }

  m_items.clear();

  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    (*it)->Release();
  }

  m_groupItems.clear();
}

void group::AddGroup( group *pGroup )
{
  if( !HasGroup( pGroup ) ) {
    pGroup->SetParent( this ); // missing from scene
    m_groupItems.push_back( pGroup );
    Dirty();
  }
}

void group::AddChild( element *pObj )
{
  if( !HasChild( pObj ) ) {
    pObj->SetParent( this );
    m_items.push_back( pObj );
    Dirty();
  }
}

void group::RemoveChild( element *pObj )
{
  items_cit cit = find(m_items.begin(), m_items.end(), pObj );
  if( cit != m_items.end() ) {
    (*cit)->SetParent(nullptr);
    m_items.erase( cit );
    pObj->Update();
    Dirty();
  }
}

void group::Render( )
{
  if( !IsVisible() ) {
    return;
  }

  for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
    if( (*it)->IsVisible() ) {
      (*it)->Render();
    }
  }

  for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
    if( (*it)->IsVisible() ) {
      (*it)->Render();
    }
  }
}

bool group::HasGroup( group *pGroup ) const
{
  return find(m_groupItems.begin(), m_groupItems.end(), pGroup ) != m_groupItems.end();
}

bool group::HasChild( element *pObj ) const
{
  return find(m_items.begin(), m_items.end(), pObj) != m_items.end();
}

element *group::FindChildByName( const string &szName )
{
  for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
    if( (*it)->HasCustomName() && (*it)->GetName() == szName ) {
      return (*it);
    }
  }

  return nullptr;
}

void group::Update( )
{
  if( m_bDirty ) {
    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->Update();
    }

    unsigned width = 1;
    unsigned height = 1;

    unsigned tmp_val = 0;

    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      tmp_val = (*it)->GetRelativeX() + (*it)->GetWidth();
      if( tmp_val > width ) {
        width = tmp_val;
      }
      tmp_val = (*it)->GetRelativeY() + (*it)->GetHeight();
      if( tmp_val > height ) {
        height = tmp_val;
      }
    }

    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      tmp_val = (*it)->GetRelativeX() + (*it)->GetWidth();
      if( tmp_val > width ) {
        width = tmp_val;
      }
      tmp_val = (*it)->GetRelativeY() + (*it)->GetHeight();
      if( tmp_val > height ) {
        height = tmp_val;
      }
    }

    SetWidth( width );
    SetHeight( height );

    element::Update();

    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      if( (*it)->IsVisible() ) {
        (*it)->Update();
      }
    }
  }
}

void group::OnMessage( const state_message &msg )
{
  if( !IsVisible() ) {
    return;
  }

  if( IsPointInside( msg.GetCursorX(), msg.GetCursorY() ) ) {
    // Update all child elements within this group

    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      if( (*it)->IsVisible() ) {
        (*it)->OnMessage( msg );
      }
    }

    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      if( (*it)->IsVisible() ) {
        (*it)->OnMessage( msg );
      }
    }
  } else {
    // Set ignored states for all child elements

    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      if( (*it)->IsVisible() ) {
        (*it)->UpdateStateRaw(false, false);
      }
    }
  }
}

};
