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
  , m_eventCallback( nullptr )
{
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
    Dirty();
  }
}

void element::SetPositionX( unsigned px )
{
  if( m_posX != px ) {
    m_posX = px;
    Dirty();
  }
}

void element::SetPositionY( unsigned py )
{
  if( m_posY != py ) {
    m_posY = py;
    Dirty();
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
    Dirty();
  }
}

void element::SetHeight( unsigned val ) {
  if( val >= 1 ) {
    m_height = val;
    Dirty();
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

void element::Dirty( )
{
  base::Dirty();
  if( GetParent() ) {
    GetParent()->Dirty();
  }
}

void element::OnMessage( const element_message &msg )
{
  const bool bInsideElement = IsPointInside( msg.GetCursorX(), msg.GetCursorY() );
  UpdateState( bInsideElement, ( bInsideElement ? msg.GetCursorState() : 0 ) );
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

void element::SetCallbackFunc( element_callback callback )
{
  m_eventCallback = callback;
}

void element::SetEventReason(element_callback_reason event, const string &szReason)
{
  if( event < cb_reason_count ) {
    m_eventReasons[event] = szReason;
  }
}

void element::OnBlur( )
{
  if( !m_eventReasons[cb_blur].empty() && m_eventCallback != nullptr ) {
    (*m_eventCallback)(this, m_eventReasons[cb_blur]);
  }
}

void element::OnFocus( )
{
  if( !m_eventReasons[cb_focus].empty() && m_eventCallback != nullptr ) {
    (*m_eventCallback)(this, m_eventReasons[cb_focus]);
  }
}

void element::OnSelect( bool bActive )
{
  if( m_eventCallback != nullptr ) {
    if( bActive ) {
      if( !m_eventReasons[cb_press].empty() ) {
        (*m_eventCallback)(this, m_eventReasons[cb_press]);
      }
    } else {
      if( !m_eventReasons[cb_release].empty() ) {
        (*m_eventCallback)(this, m_eventReasons[cb_release]);
      }
    }
  }
}

};
