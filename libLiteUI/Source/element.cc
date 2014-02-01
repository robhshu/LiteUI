//
//  liteui::element
//  Part of the libLiteUI project
//
//  Author: Robert H
//  Date:   Feb 2014
//
#include <liteui/element.h>

namespace liteui
{
element::element( const char *cTypeName )
  : base( cTypeName )
  , m_pParent( nullptr )
  , m_posX( 0 )
  , m_posY( 0 )
  , m_width( 1 )
  , m_height( 1 )
  , m_userData( 0 )
{
}

void element::SetParent( element *pParent )
{
  m_pParent = pParent;
}

void element::SetPositionX( unsigned px )
{
  m_posX = px;
}

void element::SetPositionY( unsigned py )
{
  m_posY = py;
}

void element::SetPosition( unsigned px, unsigned py )
{
  SetPositionX( px );
  SetPositionY( py );
  Update();
}

void element::SetWidth( unsigned val )
{
  if( val >= 1 ) {
    m_width = val;
    Update();
  }
}

void element::SetHeight( unsigned val ) {
  if( val >= 1 ) {
    m_height = val;
    Update();
  }
}

void element::SetUserData( unsigned val )
{
  m_userData = val;
}

element *element::GetParent( ) const
{
  return m_pParent;
}

unsigned element::GetRelativeX( ) const
{
  return m_posX;
}

unsigned element::GetRelativeY( ) const
{
  return m_posY;
}

unsigned element::GetAbsoluteX( ) const
{
  const unsigned my_x = GetRelativeX( );

  if( GetParent() ) {
    return GetParent()->GetAbsoluteX() + my_x;
  } else {
    return my_x;
  }
}

unsigned element::GetAbsoluteY( ) const
{
  const unsigned my_y = GetRelativeY( );

  if( GetParent() ) {
    return GetParent()->GetAbsoluteY() + my_y;
  } else {
    return my_y;
  }
}

unsigned element::GetUserData( ) const
{
  return m_userData;
}

unsigned element::GetWidth( ) const
{
  return m_width;
}

unsigned element::GetHeight( ) const
{
  return m_height;
}

bool element::IsPointInside( unsigned px, unsigned py ) const
{
  const unsigned ab_px = GetAbsoluteX();
  const unsigned ab_py = GetAbsoluteY();

  return( px >= ab_px && px <= ab_px + GetWidth()
    && py >= ab_py && py <= ab_py + GetHeight() );
}

};
