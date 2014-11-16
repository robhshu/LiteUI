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

void group::Release( )
{
  DecReferenceCount();

  delete this;
}

void group::Dirty( bool bAll /* = false */ )
{
  if( bAll ) {
    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      (*it)->Dirty();
    }

    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {
      (*it)->Dirty(true);
    }
  }

  base::Dirty(bAll);
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

    n_unit width_upper(0);
    n_unit height_upper(0);

    n_unit temp(0);

    for( groups_it it = m_groupItems.begin(); it != m_groupItems.end(); it++ ) {

      // is this correct here?
      (*it)->Update();

      // Relative is usually 0

      temp = (*it)->GetRelativeX() + (*it)->GetWidth();
      if (temp > width_upper) {
        width_upper = temp;
      }

      temp = (*it)->GetRelativeY() + (*it)->GetHeight();
      if (temp > height_upper) {
        height_upper = temp;
      }
    }


    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      temp = (*it)->GetRelativeX() + (*it)->GetWidth();
      if (temp > width_upper) {
        width_upper = temp;
      }

      temp = (*it)->GetRelativeY() + (*it)->GetHeight();
      if (temp > height_upper) {
        height_upper = temp;
      }
    }

    SetWidth( width_upper );
    SetHeight( height_upper );

    element::Update();

    // Now update the elements after the true width is calculated?

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
