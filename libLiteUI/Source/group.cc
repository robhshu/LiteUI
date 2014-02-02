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
}

void group::AddChild( element *pObj )
{
  if( !HasChild( pObj ) ) {
    pObj->SetParent( this );
    m_items.push_back( pObj );
    m_bDirty = true;
  }
}

void group::RemoveChild( element *pObj )
{
  items_cit cit = find(m_items.begin(), m_items.end(), pObj );
  if( cit != m_items.end() ) {
    (*cit)->SetParent(nullptr);
    m_items.erase( cit );
    pObj->Update();
    m_bDirty = true;
  }
}

void group::Render( )
{
  for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
    (*it)->Render();
  }
}

bool group::HasChild( element *pObj ) const
{
  return find(m_items.begin(), m_items.end(), pObj) != m_items.end();
}

bool group::HasChildNamed( const char *cName ) const
{
  // todo: implement
  return false;
}

void group::Update( )
{
  if( m_bDirty ) {
    unsigned width = 1;
    unsigned height = 1;

    unsigned tmp_val = 0;

    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      (*it)->Update();

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
  }
}

void group::OnMessage( unsigned px, unsigned py )
{
  // we could just send OnMessage to everything

  if( IsPointInside( px, py ) ) {
    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      (*it)->OnMessage( px, py );
    }
  } else {
    for( items_it it = m_items.begin(); it != m_items.end(); it++ ) {
      (*it)->UpdateStateRaw( false );
    }
  }

  // the group may also have callbacks from the base class
  element::OnMessage( px, py );
}

};
