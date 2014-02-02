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
element::element( const string &szTypeName )
  : base( szTypeName )
  , m_pParent( nullptr )
  , m_posX( 0 )
  , m_posY( 0 )
  , m_width( 1 )
  , m_height( 1 )
  , m_userData( 0 )
{
  for( unsigned i = 0; i < cb_reason_count; i++ ) {
    m_callbacks[i] = nullptr;
  }
}

element::~element( )
{
  m_pParent = nullptr;
}

void element::Release( )
{
  delete this;
}

void element::SetParent( element *pParent )
{
  if( m_pParent != pParent ) {
    m_pParent = pParent;
    m_bDirty = true;
  }
}

void element::SetPositionX( unsigned px )
{
  if( m_posX != px ) {
    m_posX = px;
    m_bDirty = true;
  }
}

void element::SetPositionY( unsigned py )
{
  if( m_posY != py ) {
    m_posY = py;
    m_bDirty = true;
  }
}

void element::SetPosition( unsigned px, unsigned py )
{
  SetPositionX( px );
  SetPositionY( py );
}

void element::SetWidth( unsigned val )
{
  if( val >= 1 ) {
    m_width = val;
    m_bDirty = true;
  }
}

void element::SetHeight( unsigned val ) {
  if( val >= 1 ) {
    m_height = val;
    m_bDirty = true;
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

void element::SetProperty(const string &szProperty, unsigned nValue)
{
  if( szProperty == "width" ) {
    SetWidth( nValue );
  } else if( szProperty == "height" ) {
    SetHeight( nValue );
  } else if( szProperty == "pos_x" ) {
    SetPositionX( nValue );
  } else if( szProperty == "pos_y" ) {
    SetPositionY( nValue );
  } else {
    base::SetProperty( szProperty, nValue );
  }
}

void element::OnMessage( unsigned px, unsigned py )
{
  const bool bInsideElement = IsPointInside( px, py );
  UpdateState( bInsideElement );
}

bool element::IsPointInside( unsigned px, unsigned py ) const
{
  const unsigned ab_px = GetAbsoluteX();
  const unsigned ab_py = GetAbsoluteY();

  return( px >= ab_px && px <= ab_px + GetWidth()
    && py >= ab_py && py <= ab_py + GetHeight() );
}

void element::Update( )
{
  m_bDirty = false;
}

void element::SetCallback( element_callback_reason method, element_callback callback )
{
  if( method < cb_reason_count ) {
    m_callbacks[method] = callback;
  }
}

void element::OnBlur( )
{
  if( m_callbacks[cb_blur] != nullptr ) {
    (*m_callbacks[cb_blur])(this);
  }
}

void element::OnFocus( )
{
  if( m_callbacks[cb_focus] != nullptr ) {
    (*m_callbacks[cb_focus])(this);
  }
}

};
